#include <bits/stdc++.h>

using namespace std;

const uint32_t MAX = 1u << 31, BASE = 10;
const uint32_t GROUP = 1 << 25, PERGROUP = 84;

unordered_map<uint32_t, uint32_t> CACHE;

uint32_t digit_sum(uint32_t n)
{
    uint32_t r = 0;
    while(n)
        r += n % BASE, n /= BASE;
    return r;
}

uint32_t R(uint32_t n)
{
    uint32_t r = 0, cn = n;
    while(n)
    {
        n -= digit_sum(n);
        r++;
        auto it = CACHE.find(n);
        if(it != CACHE.end())
        {
            CACHE[cn] = r + it->second;
            return r + it->second;
        }
    }
    CACHE[cn] = r;
    return r;
}

int main()
{
    ofstream out ("out.txt");
    out << "{";
    for(uint32_t i = 0; i <= MAX; i += GROUP)
    {
        cout << i << endl;
        out << "{";
        for(uint32_t n = i; n < i+PERGROUP; n++)
            out << R(n) << ",";
        out << "}";
        if(i < MAX)
            out << ",";
    }
    out << "};";
}
