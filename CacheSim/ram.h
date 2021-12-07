#pragma once
#include <string>
using std::string;

class RAM
{
private:
    int memory_size = 0;

    string *ram = nullptr; // memory storage dynamic array

    string filename;

public:
    RAM(); // default constructor

    ~RAM(); // destructor

    void set_filename(string name);

    void init_ram_zero();

    void set_memSize(int size);

    int get_memSize();

    void init_mem();

    void output();

    string *get_ram_storage();
};