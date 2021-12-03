#include <iostream>
#include <fstream>
#include <string>
#include "cache.h"
#include "ram.h"
#include "helper_functions.h"
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

Cache::Cache(string Datafilename)
{
    RAM mem;      // initialize ram
    Config setup; //configuration
    ram_memory = &mem;
    cache_setup = &setup;

    ram_memory->set_filename(Datafilename);
    ram_memory->init_mem();

    cache_setup->alloc();
}

Cache::~Cache()
{
    // destructors withing the objects already activated
    ram_memory = nullptr;
    cache_setup = nullptr;
}