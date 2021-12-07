#pragma once
#include "ram.h"
#include "config.h"
#include <cmath>
using std::log2;
/*
Holds the Cache class-> mothership of the program
*/
class Cache
{
private:
    RAM ram_memory;

    Config cache_setup;

    int *sys_parameters = nullptr;
    const int address_width = 8;
    const int line_content_size = address_width + 3; // add 3 to account for tag,valid,and dirty bit
    int S = 0;                                       // number of sets
    int s = 0;                                       // number of set index bits
    int C = 0;                                       // cache size in bytes
    int B = 0;                                       // number of blocks
    int b = 0;                                       // number of block offset bits
    int E = 0;                                       // number of lines per set
    int t = 0;                                       // number of tag bits

    // cache storage: 3-d Array of sizes [set number][lines(or associativity number)]
    string ***cache_storage = nullptr;

public:
    Cache(string Datafilename)
    {
        //initialize ram based on range input
        ram_memory.set_filename(Datafilename);
        ram_memory.init_mem();
        // setup system parameters (stored in configs array)
        cache_setup.alloc();
        // set system parameters from configuration (assignes mem location of configs arr)
        sys_parameters = cache_setup.get_SysParameters();
        //initialize all system parameters
        C = sys_parameters[0];
        B = sys_parameters[1];
        E = sys_parameters[2];
        S = C / (B * E);
        b = log2(B);
        s = log2(S);
        t = address_width - s - b;
        // initialize the cache
        init_cache();
    }

    ~Cache()
    {
        // destructors withing the objects already activated
        sys_parameters = nullptr;
        delete[] cache_storage;
        cache_storage = nullptr;
    }
    void RR(string tag,int setIndex,int blockOffset, string hexAddress);

    void set_valid_bit(int line, int setIndex, string newVBit);

    int get_valid_bit(int line, int setIndex);

    bool cache_hit_or_miss(string tag, int setIndex);

    void add_cache_block(int setIndex,int blockOffset, int random_line_index, int addressIndex);

    //creates and initializes cache storage
    void init_cache();

    bool cache_menu_handling(bool &is_quitting);

    void decode_address(string &tag, int &setIndex, int &blockOffset, string binAddress);
    /*
        takes replacement policy and address to read in hexadecimal (unparsed)
    */
    void cache_read(string hexAddress);

    void cache_write(string hexAddress, string data);

    void cache_flush();

    void cache_view();

    void memory_view();

    void cache_dump();

    void memory_dump();
};