#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <time.h>
#include <queue>

#include "config.h"
#include "cache.h"
#include "ram.h"
#include "helper_functions.h"
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::rand;
using std::string;

void Cache::init_cache()
{ // initialize the cold cache
    //initialize the 3D cache cache_storage
    string tag_and_data = "00";
    string valid_and_dirty_bits = "0"; // includes valid bit and dirty bit
    // begin memory allocation
    cache_storage = new string **[S];
    for (int setPos = 0; setPos < S; ++setPos)
    {
        cache_storage[setPos] = new string *[E];
        for (int linePos = 0; linePos < E; ++linePos)
        {
            cache_storage[setPos][linePos] = new string[line_content_size];
            for (int contentPos = 2; contentPos < line_content_size; ++contentPos)
            { // initialize the values to whatever you want the default to be
                // first three aren't data
                if (contentPos == 2) // start off the line with the valid and dirty bits
                {
                    cache_storage[setPos][linePos][0] = valid_and_dirty_bits;
                    cache_storage[setPos][linePos][1] = valid_and_dirty_bits;
                }
                cache_storage[setPos][linePos][contentPos] = tag_and_data;
            }
        }
    }
}

bool Cache::cache_menu_handling(bool &is_quitting)
{
    string options[8] = {
        "cache-read",
        "cache-write",
        "cache-flush",
        "cache-view",
        "memory-view",
        "cache-dump",
        "memory-dump",
        "quit"};

    cout << "*** Cache simulator menu ***" << endl;
    cout << "type one command:" << endl;
    for (int i = 0; i < 8; i++)
    {
        cout << i + 1 << ". " << options[i] << endl;
    }
    cout << "****************************" << endl;

    string choice = "";
    cin.ignore(1000, '\n'); //due to upcoming getline
    cout << "Enter choice:" << endl;
    getline(cin, choice);
    std::istringstream iss(choice);
    string category = "";
    iss >> category;

    int choiceNum = -1; // index of choice from option array
    for (int i = 0; i < 8; i++)
    {
        if (category == options[i])
        {
            choiceNum = i;
            break;
        }
    }

    // access commands gather additional input
    string readWrite_address = ""; // address input
    string data = "";              // data input
    switch (choiceNum)
    {
    case 0: // cache-read
        iss >> readWrite_address;
        readWrite_address = HexParser(readWrite_address); // parse hex address
        cache_read(readWrite_address);
        break;
    case 1: // cache-write
        iss >> readWrite_address;
        readWrite_address = HexParser(readWrite_address); // parse hex address
        iss >> data;
        data = HexParser(data); // parse hex data
        cache_write(readWrite_address, data);
        break;
    case 2: // cache-flush
        cache_flush();
        break;
    case 3: // cache-view
        cache_view();
        break;
    case 4: // memory-view
        ram_memory.memory_view(B);
        break;
    case 5: // cache-dump
        cache_dump();
        break;
    case 6: // memore-dump
        ram_memory.memory_dump();
        break;
    case 7: // quit
        is_quitting = true;
        break;
    default:
        cout << "invalid choice!" << endl;
        return false;
    }
    return true;
}

void Cache::decode_address(string &tag, int &setIndex, int &blockIndex, string binAddress)
{
    // number of tag bit is t
    int numTag = t;
    int numOffset = b;
    int numSet = s;

    string tempT = "";
    string tempS = "";
    string tempB = "";
    for (int i = 0; i < binAddress.size(); i++)
    {
        if (i < numTag)
        {
            tempT += binAddress[i];
            continue;
        }
        // assign tag
        tag = DectoHex(BintoDec(tempT));
        if (i < (numTag + numSet))
        {
            tempS += binAddress[i];
            continue;
        }
        setIndex = BintoDec(tempS);
        //finally do offsets
        tempB += binAddress[i];
        blockIndex = BintoDec(tempB);
    }
}

bool Cache::cache_hit_or_miss(string tag, int setIndex)
{
    // go to set index in cache storage and search for tag. If tag is not found, cache miss, else cache hit.
    for (int linePos = 0; linePos < E; ++linePos)
    {
        // tag at index 2 of cache content block
        if (cache_storage[setIndex][linePos][2] == tag && cache_storage[setIndex][linePos][0] == "1")
        {
            return true;
        }
    }
    return false;
}

void Cache::set_valid_bit(int line, int setIndex, string newVBit)
{
    cache_storage[setIndex][line][0] = newVBit;
}

int Cache::get_valid_bit(int line, int setIndex)
{
    if (cache_storage[setIndex][line][0] == "0")
    {
        return 0;
    }
    return 1;
}

void Cache::add_cache_block(int setIndex, string tag, int line, int addressIndex)
{
    // depending on block size B, and the offsetindex
    // max block offset == Block size - 1
    // first three positions in content are valid,dirty, and tag; block starts at index 3
    // total size of cache line is B + 3
    int lineSize = B + 3;
    int rootIndex = addressIndex - (addressIndex % B);
    cache_storage[setIndex][line][0] = "1";
    // add tag
    cache_storage[setIndex][line][2] = tag;

    // add block,
    for (int i = 3; i < lineSize; i++)
    {
        string byte = ram_memory.access_data(rootIndex + (i - 3));
        cache_storage[setIndex][line][i] = byte;
    }
}

void Cache::RR(string tag, int setIndex, int blockIndex, string hexAddress, int &evictionLineIndex)
{                      // random replacement of a line with address block, replace tag, update valid bit
    srand(time(NULL)); //random seed
    // get random line
    int random_line_index = rand() % E;
    //replace tag
    // if empty, no need to check for dirty bit (if dirty we write back to memory)
    for (int i = 0; i < E; i++) // check for empty lines!
    {
        if (cache_storage[setIndex][i][0] == "0")
        {
            random_line_index = i;
            break;
        }
    }
    int vBit = get_valid_bit(random_line_index, setIndex);
    int addressIndex = BintoDec(HextoBin(hexAddress));
    if (vBit == 0) // empty no need to check dirty, replace valid bit and update block
    {
        set_valid_bit(random_line_index, setIndex, "1");
        //convert address to dec, this is the index of the RAM array
        add_cache_block(setIndex, tag, random_line_index, addressIndex);
    }
    else //else if filled check for dirty bit (if dirty we write back to memory)
    {
        add_cache_block(setIndex, tag, random_line_index, addressIndex);
    }
    // update evicted line
    evictionLineIndex = random_line_index;
}

void Cache::LRU(string tag, int setIndex, int blockIndex, string hexAddress, int &evictionLineIndex)
{
}

void Cache::cache_read(string hexAddress)
{
    // first convert parsed hex address to binary
    string binAddress = HextoBin(hexAddress);
    //decode variables
    string tag = "";
    int setIndex = 0;
    int blockIndex = 0;
    //decode and assign variables
    decode_address(tag, setIndex, blockIndex, binAddress);
    //outputs:
    cout << "set:" << setIndex << endl;
    // tag in hex!
    cout << "tag:" << tag << endl;
    //Process!
    // cache hit?
    cout << "hit:";
    bool cache_hit = cache_hit_or_miss(tag, setIndex);
    int replace_policy = sys_parameters[3];
    if (cache_hit)
    {
        cache_hits += 1;
        cout << "yes\n";
        cout << "eviction_line:-1" << endl;
        cout << "ram_address:-1" << endl;
    }
    else
    {
        cache_misses += 1;
        cout << "no\n"; // cache miss!
        // add according to replacement policy
        int evictionLineIndex = 0;
        if (replace_policy == 1)
        { // random replacement
            RR(tag, setIndex, blockIndex, hexAddress, evictionLineIndex);
        }
        else
        { // Least recently used policy
            LRU(tag, setIndex, blockIndex, hexAddress, evictionLineIndex);
        }
        cout << "eviction_line:" << evictionLineIndex << endl;
        cout << "ram_address:0x" << hexAddress << endl;
    }
    cout << "data:0x" << ram_memory.access_data(HextoDec(hexAddress)) << endl;
}

void Cache::cache_write(string hexAddress, string data)
{
}

void Cache::cache_flush()
{
}

void Cache::cache_view()
{
    cout << "cache_size:" << C << endl;
    cout << "data_block_size:" << B << endl;
    cout << "associativity:" << E << endl;
    if (sys_parameters[3] == 1)
    {
        cout << "replacement_policy:"
             << "random_replacement" << endl;
    }
    else
    {
        cout << "replacement_policy:"
             << "least_recently_used" << endl;
    }
    if (sys_parameters[4] == 1)
    {
        cout << "write_hit_policy:"
             << "write_through" << endl;
    }
    else
    {
        cout << "write_hit_policy:"
             << "write_back" << endl;
    }
    if (sys_parameters[5] == 1)
    {
        cout << "write_miss_policy:"
             << "write_allocate" << endl;
    }
    else
    {
        cout << "write_miss_policy:"
             << "no_write_allocate" << endl;
    }
    cout << "number_of_cache_hits:" << cache_hits << endl;
    cout << "number_of_cache_misses:" << cache_misses << endl;
    cout << "cache_content:" << endl;
    // outputs cache storage 3d array
    for (int setPos = 0; setPos < S; ++setPos)
    {
        //cout << "Set " << setPos << endl;
        for (int linePos = 0; linePos < E; ++linePos)
        {
            //cout << "line " << linePos << endl;
            for (int contentPos = 0; contentPos < line_content_size; ++contentPos)
            {
                cout << cache_storage[setPos][linePos][contentPos] << " ";
            }
            cout << endl;
        }
    }
}

void Cache::cacheTestOutput()
{
    for (int setPos = 0; setPos < S; ++setPos)
    {
        //cout << "Set " << setPos << endl;
        for (int linePos = 0; linePos < E; ++linePos)
        {
            //cout << "line " << linePos << endl;
            for (int contentPos = 0; contentPos < line_content_size; ++contentPos)
            {
                cout << cache_storage[setPos][linePos][contentPos] << " ";
            }
            cout << endl;
        }
    }
}

void Cache::cache_dump()
{
}
