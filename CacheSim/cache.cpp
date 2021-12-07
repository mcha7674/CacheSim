#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <time.h>
#include "config.h"
#include "cache.h"
#include "ram.h"
#include "helper_functions.h"
using std::rand;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
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
    cout << "Enter choice: " << endl;
    cin >> choice;

    int choiceNum = -1; // index of choice from option array
    for (int i = 0; i < 8; i++)
    {
        if (choice == options[i])
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
        cin >> readWrite_address;
        readWrite_address = HexParser(readWrite_address); // parse hex address
        cache_read(readWrite_address);
        break;
    case 1: // cache-write
        cin >> readWrite_address;
        readWrite_address = HexParser(readWrite_address); // parse hex address
        cin >> data;
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
        memory_view();
        break;
    case 5: // cache-dump
        cache_dump();
        break;
    case 6: // memore-dump
        memory_dump();
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

    string temp = "";
    for (int i = 0; i < binAddress.size(); i++)
    {
        if (i < numTag)
        {
            temp += binAddress[i];
            continue;
        }
        // assign tag
        tag = DectoHex(BintoDec(temp));
        temp = "";
        if (i < (numTag + numSet))
        {
            temp += binAddress[i];
            continue;
        }
        setIndex = BintoDec(temp);
        temp = "";
        //finally do offsets
        temp += binAddress[i];
        blockIndex = BintoDec(temp);
    }
}

bool Cache::cache_hit_or_miss(string tag, int setIndex)
{
    // go to set index in cache storage and search for tag. If tag is not found, cache miss, else cache hit.
    for (int linePos = 0; linePos < E; ++linePos)
    {   
        // tag at index 2 of cache content block
        if (cache_storage[setIndex][linePos][2] == tag)
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
    if(cache_storage[setIndex][line][0] == "0"){return 0;}
    return 1;
}

void Cache::add_cache_block(int setIndex, int blockOffsetIndex, int random_line_index, int addressIndex)
{
    // depending on block size B, and the offsetindex

    

}

void Cache::RR(string tag,int setIndex, int blockOffset, string hexAddress)
{ // random replacement of a line with address block, replace tag, update valid bit
    srand(time(NULL)); //random seed
    // get random line
    int random_line_index = rand() % E;
    //replace tag
    // if empty, no need to check for dirty bit (if dirty we write back to memory)
    int vBit = get_valid_bit(random_line_index, setIndex);
    if (vBit == 0) // empty no need to check dirty, replace valid bit and update block
    {
        set_valid_bit(random_line_index,setIndex, "1");
        //convert address to dec, this is the index of the RAM array
        int addressIndex = BintoDec(HextoBin(hexAddress));
        add_cache_block(setIndex,blockOffset, random_line_index, addressIndex); 
    }
    else
    {

    }
    //else if filled check for dirty bit (if dirty we write back to memory)
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
        cout<<"yes\n";
        cout << "eviction_line:-1" <<endl;
        cout << "ram_address:-1" <<endl;
        
    }
    else
    {
        cout<<"no\n"; // cache miss!
        // add according to replacement policy
        if (replace_policy == 1)
        { // random replacement

        }
        else{ // Least recently used
            
        }
        cout << "eviction_line:" <<endl;
        cout << "ram_address:" <<endl;
    }
    


}

void Cache::cache_write(string hexAddress, string data)
{
}

void Cache::cache_flush()
{
}

void Cache::cache_view()
{
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

void Cache::memory_view()
{
    cout <<"memory_size:"<<ram_memory.get_memSize()<<endl;
    cout <<"memory_content:";
   for (int i = 0; i < ram_memory.get_memSize(); i++)
    {
        if (i % B == 0) //start of new line
        {
            cout << "\n0x" << DectoHex(i) << ":";
        }
        //cout << ram_memory.get_ram_storage()[i]<< " ";
        
        //cout << ram_memory.get_ram_storage()[i]<< endl;
  
    }
}

void Cache::cache_dump()
{
}

void Cache::memory_dump()
{
}