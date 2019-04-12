#include <bits/stdc++.h>
#include "gralib.hpp"

using namespace std;

const size_t NAX = 1 << 18;

int main()
{
    uint32_t n = dajN(), k = dajK(), M = dajM();

    vector<bool> prime(n+1);
    vector<vector<uint32_t>> divisors(n+1, {1});
    for(uint32_t i = 2; i <= n; i++)
    {
        divisors[i].push_back(i);
        for(uint32_t x = 2*i; x <= n; x += i)
            prime[x] = false, divisors[x].push_back(i);
    }

    vector<double> avg_gain(n+1);
    for(uint32_t x = 0; x <= n; x++)
    {
        uint32_t c = 0;
        for(uint32_t y : divisors[x])
            if(y <= k)
                avg_gain[x] += y, c++;
        avg_gain[x] /= k;
    }

    uint32_t _max_calls = 0, _sum_calls = 0;
    for(uint32_t t = 0; t < 100; t++)
    {
        uint32_t x = 0;
        while(x < n-2*k)
        {
            uint32_t y = nastepna();
            if(x + y <= n and x % y == 0 and y >= k/3 and y >= floor(avg_gain[x]) and not prime[y])
                zwieksz(), x += y;
        }
        while(x < n)
        {
            uint32_t y = nastepna();
            if(x + y <= n and x % y == 0)
                zwieksz(), x += y;
        }
#ifdef XHOVA
        _max_calls = max(_max_calls, (uint32_t)__calls);
        _sum_calls += __calls;
#endif
        koniec();
    }
    cerr << "max calls: " << _max_calls << endl;
    cerr << "avg calls: " << fixed << setprecision(3) << (double)_sum_calls/100 << endl;
}