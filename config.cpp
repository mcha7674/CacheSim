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
        "replacement policy: ",
        "write hit policy: ",
        "write miss policy: "};
    // maybe enumerate this instead
    Type type[6] = {C, B, E, RP, WH, WM}; // for enumeration of is_valid
    int i = 0;
    cout << "configure the cache:" << endl;
    while (i < 6)
    {
        cout << prompts[i];
        cin >> configs[i];
        if (!is_valid(type[i], configs[i]))
        {
            cout << "Invalid input!" << endl;
            continue;
        }
        i++;
    }
    cout << "cache successfully configured!" << endl;
}

bool Config::is_valid(Type type, int parameter)
{
    bool valid = true;
    // breaks defaults to valid = true;
    switch (type)
    {
    case 0:
        // Cache size
        if (parameter < 8 || parameter > 256)
        {
            return false;
        }
        break;
    case 1:
        // block size
        break;
    case 2:
        // associativity
        if (parameter == 1 || parameter == 2 || parameter == 4)
        {
            break;
        }
        return false;
    case 3:
        // replacement policy
    case 4:
        // Write hit policy
    case 5:
        // write miss policy
        if (parameter == 1 || parameter == 2)
        {
            break;
        }
        return false;
    default:
        break;
    }
    return valid;
}

int *Config::get_SysParameters()
{
    int *SysPar = configs; // points to memory location of configs array
    return SysPar; // return the pointer!
}

void Config::view_inputs()
{
    string prompts[6] = {
        "cache size: ",
        "data block size: ",
        "associativity: ",
        "replacement policy: ",
        "write hit policy: ",
        "write miss policy: "};
    int i = 0;
    for (auto prompt:prompts)
    {
        cout << prompt << configs[i] << endl;
        i++;
    }
}