#include <bits/stdc++.h>

using namespace std;

uint32_t log2floor(uint64_t x) { return 63 - __builtin_clzll(x); }
uint32_t popcount(uint64_t x) { return __builtin_popcountll(x); }

// sum(popcount(i) for i in range(n))
uint64_t popcount_sum(uint64_t n)
{
    uint64_t r = 0, b = 0;
    for(uint32_t i = log2floor(n)+1; i --> 0; )
    {
        if((n>>i) & 1)
        {
            r += (1LLU << (i-1)) * i;
            r += (1LLU << i) * b;
            b++;
        }
    }
    return r;
}

int main()
{
    uint64_t a, b;
    cin >> a >> b;
    cout << popcount_sum(b+1) - popcount_sum(a);
}
