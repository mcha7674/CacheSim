#pragma once

class Config
{
private:
    int cache_size = 0;
    int block_size = 0;
    int associativity = 0;
    int replacement_policy = 0;
    int write_hit_policy = 0;
    int write_miss_policy = 0;

    //system parameters
    int configs[6] = {
        cache_size,
        block_size,
        associativity,
        replacement_policy,
        write_hit_policy,
        write_miss_policy};

    enum Type
    {
        C = 0,
        B,
        E,
        RP,
        WH,
        WM
    };

    bool is_valid(Type type, int parameter);

public:
    Config(){};

    void alloc();

    int* get_SysParameters();

    void view_inputs();

};