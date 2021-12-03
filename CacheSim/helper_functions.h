#pragma once
#include <string>
using std::string;

/*
The idea is to extract the digits of a given hexadecimal 
number starting from the rightmost digit 
and keep a variable dec_value. 
At the time of extracting digits from the hexadecimal number, 
multiply the digit with the proper base (Power of 16) and add it to the variable dec_value.
In the end, the variable dec_value will store the required decimal number.
*/
int HextoDec(string hexVal);

string HextoBin(string hexVal);

string DectoHex(int decVal);