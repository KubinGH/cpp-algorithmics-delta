#include <bits/stdc++.h>
#include "cyklib.hpp"

using namespace std;

const uint32_t MAX_N = 2000;

mt19937 gen(42);
uint32_t randint(uint32_t a, uint32_t b)
{
    return uniform_int_distribution<uint32_t>{a, b}(gen);
}

uint64_t randquery()
{
    do {
        uint64_t x = randint(1, 1e9), y = x;
        for(uint32_t i = 2; i <= MAX_N; i++)
            while(y % i == 0)
                y /= i;
        if(y == 1)
            return x;
    } while(true);
}

int main()
{
    uint64_t rot = 0;
    vector<pair<uint64_t, uint64_t>> occ;
    occ.emplace_back(0, circular_shift(0));
    
    vector<uint64_t> hit, miss;
    for(uint32_t q = 0; q < 94; q++)
    {
        uint64_t x = randquery();
        rot += x;
        uint64_t val = circular_shift(x);
        for(auto p : occ)
        {
            if(p.second == val)
                hit.push_back(rot - p.first);
            else
                miss.push_back(rot - p.first);
        }
        occ.emplace_back(rot, val);
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
            uint64_t val = circular_shift(n);
            if(occ.back().second == val)
            {
                cerr << n << endl;
                give_answer(n);
                return 0;
            }
            else
                occ.emplace_back(rot += n, val);
        }
    }
}