#include <bits/stdc++.h>

using namespace std;

struct action { uint32_t t; int64_t q, dx, dy; };

int main()
{
    int64_t a, b, c, p; uint32_t n;
    cin >> a >> b >> c >> n >> p;
    unordered_map<uint32_t, map<pair<uint32_t, uint32_t>, int64_t>> M;
    vector<tuple<uint32_t, uint32_t, int64_t, int64_t, int64_t>> A;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t z;
        cin >> z;
        while(z --> 0)
        {
            uint32_t t; int64_t q, dx, dy;
            cin >> t >> q >> dx >> dy; t--;
            A.emplace_back(i, t, q, dx, dy);
        }
    }
    M[0][{0, 0}] = 1;
    uint64_t r = 0;
    while(p --> 0)
    {
        cerr << r << "\n";
        uint64_t x = 0;
        for(auto kv : M)
        {
            for(auto w : kv.second)
                x += w.second * (w.first.first*a + w.first.second*b + c);
        }
        auto N = M;
        for(auto a : A)
        {
            uint32_t i, t; int64_t q, dx, dy;
            tie(i, t, q, dx, dy) = a;
            for(auto w : M[i])
                N[t][{w.first.first+dx, w.first.second+dy}] += q * w.second;
        }
        M = N;
        r += x;
    }
    cout << r;
}
