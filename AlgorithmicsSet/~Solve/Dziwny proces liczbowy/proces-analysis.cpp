#include <bits/stdc++.h>

using namespace std;

uint64_t f(uint64_t x)
{
    uint64_t r = 0;
    while(x)
    {
        r += (x%10) * (x%10);
        x /= 10;
    }
    return r;
}

int main()
{
    set<uint64_t> S;
    map<uint64_t, uint64_t> M;
    for(uint32_t i = 1; i <= (1<<20); i++)
    {
        if(M.find(i) != M.end())
            continue;
        uint32_t x = i;
        while(S.find(f(x)) == S.end())
        {
            x = f(x);
            S.insert(x);
        }
        for(uint32_t x : S)
            M[x] = *S.begin();
        S.clear();
    }
    for(uint32_t i = 1; i <= (1<<20); i++)
    {
        if(M[i] == 0)
            continue;
        cout << i << ": " << M[i] << endl;
    }
}
