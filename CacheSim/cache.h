#pragma once
#include "ram.h"
#include "config.h"
/*
Holds the Cache class-> mothership of the program
*/
class Cache
{
private:
    RAM *ram_memory = nullptr;

    Config *cache_setup = nullptr;

    int *sys_parameters = nullptr;

    // cache storage: 3-d Array of sizes [set number][lines(or associativity number)] 
    string ***cache_storage = nullptr;

public:
    Cache::Cache(string Datafilename)
    {
        RAM mem;      // initialize ram
        Config setup; //configuration
        ram_memory = &mem;
        cache_setup = &setup;

        //initialize ram based on range input
        ram_memory->set_filename(Datafilename);
        ram_memory->init_mem();

        // setup system parameters (stored in configs array)
        cache_setup->alloc();

        // set system parameters from configuration
        sys_parameters = cache_setup->get_SysParameters();

    }

    Cache::~Cache()
    {
        // destructors withing the objects already activated
        ram_memory = nullptr;
        cache_setup = nullptr;
        sys_parameters = nullptr;
        cache_storage = nullptr;
    }

    //creates and initializes cache storage
    void init_cache();

    void cache_menu();
    /*
        takes replacement policy and address to read in hexadecimal (unparsed)
    */
    void cache_read(int rep_policy, string hexAddress);

    void cache_write(int write_policy);

    void cache_flush();

    void cache_view();

    void memory_view();

    void cache_dump();

    void memory_dump();
};