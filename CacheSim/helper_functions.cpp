#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;



int HextoDec(string hexVal)
{
    int len = hexVal.size();
    int base = 1;
    int dec_val = 0;
    for (int i = len - 1; i >= 0; i--) {
        if (hexVal[i] >= '0' && hexVal[i] <= '9') {
            dec_val += (int(hexVal[i]) - 48) * base;
            base = base * 16;
        }
        else if (hexVal[i] >= 'A' && hexVal[i] <= 'F') {
            dec_val += (int(hexVal[i]) - 55) * base;
            base = base * 16;
        }
    }
    return dec_val;
}

string HextoBin(string hexVal)
{
    long int i = 0;
    string bin = "";
 
    while (hexVal[i]) {
 
        switch (hexVal[i]) {
        case '0':
            bin += "0000";
            break;
        case '1':
            bin += "0001";
            break;
        case '2':
            bin += "0010";
            break;
        case '3':
            bin += "0011";
            break;
        case '4':
            bin += "0100";
            break;
        case '5':
            bin += "0101";
            break;
        case '6':
            bin += "0110";
            break;
        case '7':
            bin += "0111";
            break;
        case '8':
            bin += "1000";
            break;
        case '9':
            bin += "1001";
            break;
        case 'A':
        case 'a':
            bin += "1010";
            break;
        case 'B':
        case 'b':
            bin += "1011";
            break;
        case 'C':
        case 'c':
            bin += "1100";
            break;
        case 'D':
        case 'd':
            bin += "1101";
            break;
        case 'E':
        case 'e':
            bin += "1110";
            break;
        case 'F':
        case 'f':
            bin += "1111";
            break;
        default:
            bin = "\nInvalid hexadecimal digit ";
        }
        i++;
    }
    return bin;
}


string DectoHex(int decVal)
{ // max will be 256
    vector <char> hexaDeciNum;
    string Hex = "";
    if (decVal == 0)
    {
        return "00";
    }
    while (decVal != 0) {
        // temporary variable to store remainder
        int temp = 0;
 
        // storing remainder in temp variable.
        temp = decVal % 16;
 
        // check if temp < 10
        if (temp < 10) {
            hexaDeciNum.push_back(temp + 48);
        }
        else {
            hexaDeciNum.push_back(temp + 55);
        }
        decVal = decVal / 16;
    }
    // if only one value was stored, then the left most digit is 0
    if (hexaDeciNum.size() == 1){hexaDeciNum.push_back('0');}
    // printing hexadecimal number array in reverse order
    Hex += hexaDeciNum[1];
    Hex += hexaDeciNum[0];
    return Hex;
}