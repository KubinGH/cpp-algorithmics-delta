#include <bits/stdc++.h>

using namespace std;

unordered_map<uint64_t, bool> CACHE;
bool X(uint64_t n)
{
    if(n == 1)
        return true;
    else if(n == 2)
        return false;
    else if(n == 3)
        return true;
    else
    {
        if(CACHE.find(n) != CACHE.end())
            return CACHE[n];
        CACHE[n] = (not X(n/2)) or (not X(n-1));
        return CACHE[n];
    }
}

int main()
{
    uint32_t q;
    cin >> q;
    for(uint32_t i = 0; i < q; i++)
    {
        uint64_t n;
        cin >> n;
        if(X(n))
            cout << "TAK\n";
        else
            cout << "NIE\n";
    }
}
