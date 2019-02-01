#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

unordered_map<int64_t, uint32_t> cache;
uint32_t gamma(int64_t x, const vector<int64_t>& F)
{
    if(x == 0) return 0;
    if(x <= 3) return 1;
    if(cache.find(x) != cache.end())
        return cache[x];
    uint32_t m = upper_bound(F.begin(), F.end(), x) - F.begin();
    return cache[x] = min(gamma(x - F[m-1], F), gamma(F[m] - x, F)) + 1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    vector<int64_t> F = {0, 1};
    while(F.back() < (int64_t)1e18)
        F.push_back(F.end()[-1] + F.end()[-2]);
    cache.reserve(1 << 20);
    uint32_t p;
    cin >> p;
    while(p --> 0)
    {
        int64_t x;
        cin >> x;
        cout << gamma(x, F) << "\n";
    }
}
