#include <bits/stdc++.h>

using namespace std;

vector<uint64_t> F;

map<pair<uint64_t, uint32_t>, uint64_t> CACHE;
uint64_t fin(uint64_t x, uint32_t f)
{
    if(x == 0)
        return 1;
    if(f == 0)
        return 0;
    if(CACHE.find({x, f}) != CACHE.end())
        return CACHE[{x, f}];
    return (CACHE[{x, f}] = (fin(x, f - 1) + (x >= F[f-1] ? fin(x - F[f-1], f - 1) : 0)));
}
uint64_t fic(uint64_t x)
{
    uint64_t r = 0;
    for(uint64_t i = F.size(); i --> 0 and x; )
    {
        if(x >= F[i])
            x -= F[i], r++;
    }
    return r;
}

int main()
{
    F.push_back(1); F.push_back(2);
    while(F.back() <= (uint64_t)1e18)
        F.push_back(F[F.size() - 1] + F[F.size() - 2]);
    for(uint64_t n = 1; n <= 1024; n++)
        cout << n << ": " << fin(n, F.size()) << endl;
}
