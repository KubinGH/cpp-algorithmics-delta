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
    for(uint64_t i = 1; i <= (1<<15); i++)
    {
        if(M.find(i) != M.end())
            continue;
        uint64_t x = i;
        while(S.find(f(x)) == S.end())
        {
            x = f(x);
            S.insert(x);
        }
        for(uint64_t x : S)
            M[x] = *S.begin();
        S.clear();
    }
    uint64_t n;
    cin >> n;
    while(f(n) < n)
        n = f(n);
    if(M.find(n) != M.end())
        cout << M[n];
    else
        cout << 0;
}
