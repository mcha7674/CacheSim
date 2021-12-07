#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "helper_functions.h"
#include "ram.h"
#include "config.h"
#include "cache.h"

using namespace std;

// first arg is number of command-line args and second is a list of them
int main(int argc, char *argv[])
{
	string Datafilename = argv[argc - 1]; // grabs command line file arg
	/*
	ifstream myfile(Datafilename);
	string data;
	if (myfile.is_open())
	{

		while (getline(myfile, data))
		{ // add values to ram array

			cout << data << endl;
		}

		myfile.close();
	}

	else
		cout << "Unable to open file";
	*/
	/*
	string hex = "FF";
	int dec = 130;
	cout << HextoBin(hex) << endl;
	cout << HextoDec(hex)<<endl;
	cout << DectoHex(dec)<<endl;
	*/
	//string test = HexParser("0xFF");
	///cout << test << endl;
	//RAM mem;
	//mem.set_filename(Datafilename);
	//mem.init_mem();
	//cout <<mem.get_memSize()<<endl;
	//mem.Testoutput();
	//Config configuration;
	//configuration.alloc();

	//testing decode
	/*
	Cache cache(Datafilename);
	string tag = "";
	int numOffset = 0;
	int setIndex = 0;
	string bin = HextoBin("60");
	cout << "address binary is: " << bin << endl;
	cache.decode_address(tag, setIndex, numOffset, bin);
	cout << "tag: " << tag << endl;
	cout << "set index: " << setIndex << endl;
	cout << "b: " << numOffset << endl;
	*/
	/*
	Cache cache(Datafilename);
	cache.cache_read("03");
	cache.cache_view();
	cache.add_cache_block(0, 0, 3);
	cache.cache_view();
	*/

	//TESTING MEM VIEW
	/*
	RAM ram_memory;
	ram_memory.set_filename(Datafilename);
	ram_memory.init_mem();
	ram_memory.output();
	ram_memory.memory_view(8);
	*/

	//menu tests
	/*
	bool is_quitting = false;
	Cache cache(Datafilename);
	cache.cache_menu_handling(is_quitting);
	*/

	/*
	Cache cache(Datafilename);
	cout << "\nInitializing cache..."
		 << endl;
	cache.init_cache();
	cout << "Cache initialized successfully!\n"
		 << endl;

	bool is_quitting = false;
	while (!is_quitting)
	{
		cout << endl;
		bool valid_choice = cache.cache_menu_handling(is_quitting);
		if (!valid_choice)
		{
			continue; // start loop again from beginning
		}
	}
	*/

	return 0;
}