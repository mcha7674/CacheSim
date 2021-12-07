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
    string data = "";
    ifstream myfile(filename);

    // ask for range and parse input
    string buffer = ""; // grabs init-ram
    string start = "";  // grabs start (its always 0)
    string end = "";    // end is gonna be our range value!

    cout << "initialize the RAM:\n";
    cin >> buffer >> start >> end;
    end = HexParser(end);
    // set the memory size
    set_memSize(HextoDec(end) + 1);

    if (myfile.is_open())
    {
        int i = 0;
        while (i < memory_size)
        { // add values to ram array
            getline(myfile, data);
            // make sure i dont grab end characters like /r or /n
            string byte = "";
            byte += data[0];
            byte += data[1];
            ram[i] = byte;
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

void RAM::memory_view(int blockSize)
{
    cout << "memory_size: " << memory_size << endl;
    cout << "memory_content" << endl
         << "Address:Data" << endl;

    for (int i = 0; i < memory_size; ++i)
    {
        if (i == 0)
        {
            cout << "Ox00:" << ram[0] << " ";
        }

        else if (i % blockSize == 0)
        {
            cout << endl;
            cout << "0x" << DectoHex(i) << ":" << ram[i] << " ";
        }
        else
        {
            cout << ram[i] << " ";
        }
    }
}

void RAM::memory_dump()
{
}

string RAM::access_data(int addressIndex)
{
    return ram[addressIndex];
}

void RAM::update_data(int addressIndex, string data)
{
    ram[addressIndex] = data;
}