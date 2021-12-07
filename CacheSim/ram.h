#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

class RAM
{
private:
    int memory_size = 0;

    vector<string> ram; // memory storage dynamic array

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

    void memory_view(int blockSize);

    void memory_dump();

    string access_data(int addressIndex);
};