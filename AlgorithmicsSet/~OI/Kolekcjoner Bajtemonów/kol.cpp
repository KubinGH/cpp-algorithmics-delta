#include <bits/stdc++.h>

using namespace std;

#ifdef XHOVA
vector<size_t> __A;
size_t __n, __p = 0, __r;
int karta() { if(__p == __n) { __p = 0; return 0; } else return __A[__p++]; }
void odpowiedz(int wynik) { assert(wynik == (int)__r); exit(0); }
#else
#include "ckollib.h"
#endif

int main()
{
#ifdef XHOVA
    cin >> __n >> __r;
    __A.resize(__n);
    for(auto& a : __A) cin >> a;
#endif
    uint32_t a1 = 0, c1 = 1, a2 = 0, c2 = 1;
    uint32_t curr;
    const uint64_t M = 1 << 16;
    static uint64_t d[2][M];
    while( (curr = karta()) )
    {
        if(not a1)
            a1 = curr;
        else if(a1 == curr)
            c1++;
        else if(not a2)
            a2 = curr;
        else if(a2 == curr)
            c2++;

        d[0][curr % M]++;
        d[1][curr / M]++;
    }

    if(a1 and a2)
    {
        if(c1 != c2)
            odpowiedz(c1 < c2 ? a1 : a2);
        uint32_t c = c1;
        for(uint32_t t = 0; t < 2; t++)
            for(uint32_t x = 0; x < M; x++)
                d[t][x] %= c;
        uint32_t d0 = 0, d1 = 0;
        for(uint32_t x = 0; x < M; x++)
        {
            if(d[0][x]) d0 = x;
            if(d[1][x]) d1 = x;
        }
        odpowiedz(d0 + d1*M);
    }
    else
        odpowiedz(a1);
}
