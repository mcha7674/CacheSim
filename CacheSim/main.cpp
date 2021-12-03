#include <iostream>
#include "helper_functions.h"
#include "ram.h"
#include "config.h"


using namespace std;


int main()
{
	/*
	string hex = "FF";
	int dec = 130;
	cout << HextoBin(hex) << endl;
	cout << HextoDec(hex)<<endl;
	cout << DectoHex(dec)<<endl;
	*/
	RAM mem(256, "input.txt");
	cout <<mem.get_memSize()<<endl;
	mem.Testoutput();
	//Config configuration;
	//configuration.alloc();
		
	return 0;
}