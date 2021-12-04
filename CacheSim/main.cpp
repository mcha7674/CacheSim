#include <iostream>
#include <fstream>
#include <string>
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

	Cache cache(Datafilename);

	return 0;
}