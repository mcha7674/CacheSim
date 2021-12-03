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

public:
    Cache(string Datafilename);

    ~Cache();

    void cache_read(int rep_policy);

    void cache_write(int write_policy);

    void cache_flush();

    void cache_view();

    void memory_view();

    void cache_dump();

    void memory_dump();
};