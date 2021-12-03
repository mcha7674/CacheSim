#include <iostream>
#include <fstream>
#include <string>
#include "ram.h"
#include "helper_functions.h"
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::string;

RAM::RAM(int size, string filename)
{
    memory_size = size;
    if (filename != "")
    {
        init_mem(filename);
    }
}


RAM::~RAM()
{
    delete[] ram;
    ram = nullptr;
    memory_size = 0;
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
    ram = new string[memory_size];
    for(int i = 0;i < memory_size; i++)
    {   // add values to ram array
        ram[i] = "00";
    }
}


void RAM::init_mem(string file_name)
{
    string data;
    ifstream myfile (file_name);

    //initialize ram array
    init_ram_zero();

    // ask for range
    string buffer = "";
    string start = "";
    string end = "";
    cout <<"initialize the RAM:\n";
    cin >>buffer>>start>>end;
    
    if (myfile.is_open())
    {
        int i = 0;
        while ( getline (myfile,data) )
        {   // add values to ram array
            ram[i] = data;
            i++;
        }
        myfile.close();
    }

    else cout << "Unable to open file";
    
}

void RAM::Testoutput()
{
    for (int i = 0; i < memory_size; i++)
    {
        cout<<"0x"<<DectoHex(i)<<":"<<ram[i]<<endl;
    }
}

