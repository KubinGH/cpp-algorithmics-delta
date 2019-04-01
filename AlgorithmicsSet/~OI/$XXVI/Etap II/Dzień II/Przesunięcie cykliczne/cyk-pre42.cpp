#include <bits/stdc++.h>
#include "cyklib.hpp"

using namespace std;

const uint32_t MAX_N = 2048, MAX_Q = 100;

mt19937 gen(42);
uint32_t randint(uint32_t a, uint32_t b)
{
    return uniform_int_distribution<uint32_t>{a, b}(gen);
}

int main()
{
    uint64_t rot = 0;
    unordered_map<uint64_t, uint64_t> occ;
    occ[0] = circular_shift(0);
    
    vector<uint64_t> hit, miss;
    for(uint32_t q = 1; q < MAX_Q; q++)
    {
        uint64_t x = randint(1, 1e9);
        rot += x;
        uint64_t val = circular_shift(x);
        for(auto p : occ)
        {
            if(p.second == val)
                hit.push_back(rot - p.first);
            else
                miss.push_back(rot - p.first);
        }
        occ[rot] = val;
    }
    for(uint32_t n = 1; n <= MAX_N; n++)
    {
        bool all_hit = true, all_miss = true;
        for(uint64_t x : hit)
        {
            if(x % n)
            {
                all_hit = false;
                break;
            }
        }
        for(uint64_t x : miss)
        {
            if(x % n == 0)
            {
                all_miss = false;
                break;
            }
        }
        if(all_hit and all_miss)
        {
            give_answer(n);
            return 0;
        }
    }
}