/*
XXX    XXX  DDDDDD
 XXX  XXX   DDD DDD
  XXXXXX    DDD  DDD
   XXXX     DDD  DDD
   XXXX     DDD  DDD
  XXX XXX   DDD  DDD
 XXX   XXX  DDD DDD
XXX     XXX DDDDDD
*/

#include <bits/stdc++.h>

using namespace std;

constexpr size_t P = /* 24 */ 13;
constexpr uint pr[] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 
    43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89
};
const size_t SIEVELIM = 1e7;

uint n;
vector<pair<uint, uint>> worthy;

void gen(size_t i, uint v, uint d, uint e)
{
    if(i == P and v >= n/2 and v <= n)
        worthy.emplace_back(v, d);
    else if(i == P or v > n)
        {}
    else
    {
        gen(i, v * pr[i], d, e + 1);
        gen(i + 1, v, d * (e + 1), 0);
    }
}

uint divs(uint x)
{
    uint d = 1;
    for(size_t i = 0; i < P; i++)
    {
        auto p = pr[i];
        uint e = 0;
        while(x % p == 0)
            x /= p, e++;
        d *= e + 1;
    }
    return d;
}

int main()
{
    cin >> n;

    vector<uint> sigma;
    if(n < SIEVELIM)
    {
        sigma.resize(n+1);
        for(size_t i = 1; i <= n; i++)
            for(size_t x = i; x <= n; x += i)
                sigma[x]++;
    }

    gen(0, 1, 1, 0);
    sort(worthy.begin(), worthy.end());
    cerr << "[" << worthy.size() << "]" << endl;

    tuple<uint, uint, uint> result = {1, 1, 1};
    for(auto [x, a] : worthy)
        for(auto [y, b] : worthy)
    {
        if(y > x)
            break;
        result = max(result, {a + b - (n < SIEVELIM ? sigma[gcd(x, y)] : divs(gcd(x, y))), x, y});
    }

    cout << get<0>(result) << '\n' << get<1>(result) << ' ' << get<2>(result) << endl;
}