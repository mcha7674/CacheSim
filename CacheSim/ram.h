#pragma once
#include <string>
using std::string;

class RAM
{
    private:
        int memory_size = 0;

        string *ram = nullptr;

        const int start = 0; 

        int end = 0; // max 255

    public:
        RAM(); // default constructor

        RAM(int size = 0, string filename = ""); // constructor

        ~RAM(); // destructor

        void init_ram_zero();

        void set_memSize(int size);

        int get_memSize();

        void init_mem(string file_name);

        void mem_view(string filename);

        void mem_dump(string filename);
        
        void Testoutput();
};