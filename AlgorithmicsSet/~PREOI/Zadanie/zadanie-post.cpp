#include <bits/stdc++.h>
#ifndef _WIN32
#define putchar putchar_unlocked
#endif

using namespace std;

const size_t MAX = 1<<20;

void load_uint32(uint32_t& x)
{
    x = 0;
    char lchar;
    while(not isdigit(lchar = getchar())) {}
    do {
        x *= 10, x += lchar - '0';
    } while(isdigit(lchar = getchar()));
}

int main()
{
    uint32_t t;
    load_uint32(t);
    for(uint32_t ti = 0; ti < t; ti++)
    {
        uint32_t n;
        load_uint32(n);
        static uint32_t P[MAX], T[MAX];
        static char S[MAX];
        for(uint32_t i = 0; i < n; i++)
            load_uint32(P[i]);
        S[0] = 'a'; bool ok = true;
        uint32_t j = 0;
        for(uint32_t i = 1; i < n; i++)
        {
            if(P[i] == 0)
                S[i] = 'b';
            else
                S[i] = S[P[i]-1];
            while(j > 0 and S[j] != S[i])
                j = T[j-1];
            if(S[j] == S[i])
                j++;
            T[i] = j;
            if(T[i] != P[i])
                { ok = false; break; }
        }
        if(ok)
        {
            puts("TAK");
            S[n] = '\0';
            puts(S);
        }
        else
            puts("NIE");
    }
}
