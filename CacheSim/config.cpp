#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include "config.h"
using namespace std;


void Config::alloc()
{
    string prompts[6] = {
        "cache size: ",
        "data block size: ",
        "associativity: ",
        "replacement policy ",
        "write hit policy: ",
        "write miss policy: "
    };
    // maybe enumerate this instead
    Type type[6] = {C, B, E, RP, WH, WM}; // for enumeration of is_valid
    int i = 0;
    while(i < 6)
    {
        cout <<prompts[i];
        cin >> configs[i];
        if (!is_valid(type[i],configs[i]))
        {
            cout <<"\nInvalid input!"<<endl;        
            continue;
        }
        cache_size = configs[i];
        cout << endl; // and continue
        i++;   
    }
}

bool Config::is_valid(Type type, int parameter)
{
    bool valid = false;
    switch (type)
    {
        case 0:
            // Cache size
            if (cache_size >= 8 && cache_size <= 256)
            {
                valid = false;
            }
            break;
        case 1:
            // block size
            if (false)
            {
                valid = false;
            }
            break;
        case 2:
            // associativity
            break;
        case 3:
            // replacement policy
            break;
        case 4:
            // Write hit policy
            break;
        case 5:
            // write miss policy
            break;
        default:
            valid = true;
            break;
    }
    return valid;
}