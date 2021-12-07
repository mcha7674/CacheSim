#include <iostream>
#include <fstream>
#include <string>
#include "ram.h"
#include "helper_functions.h"
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

RAM::RAM() // default constructor
{
    //initialize ram array to all zero data
    init_ram_zero();
}

RAM::~RAM()
{
    delete[] ram;
    ram = nullptr;
    memory_size = 0;
}

void RAM::set_filename(string name)
{
    filename = name;
}

void RAM::set_memSize(int size)
{
    memory_size = size;
}

int RAM::get_memSize()
{
    return memory_size;
}

void RAM::init_ram_zero()
{
    ram = new string[256];
    for (int i = 0; i < 256; i++)
    { // add values to ram array
        ram[i] = "00";
    }
}

void RAM::init_mem()
{
    string data;
    ifstream myfile(filename);

    // ask for range and parse input
    string buffer = ""; // grabs init-ram
    string start = "";  // grabs start (its always 0)
    string end = "";    // end is gonna be our range value!

    cout << "initialize the RAM:\n";
    cin >> buffer >> start >> end;
    end = HexParser(end);
    // set the memory size
    set_memSize(HextoDec(end)+1);

    if (myfile.is_open())
    {
        int i = 0;
        while (i < memory_size)
        { // add values to ram array
            getline(myfile, data);
            ram[i] = data;
            i++;
        }
        cout << "RAM successfully initialized!" << endl;
        myfile.close();
    }

    else
        cout << "Unable to open file";
}

void RAM::output()
{
    for (int i = 0; i < 256; i++)
    {
        cout << "0x" << DectoHex(i) << ":" << ram[i] << endl;
    }
}


string *RAM::get_ram_storage()
{
    return ram;
}
