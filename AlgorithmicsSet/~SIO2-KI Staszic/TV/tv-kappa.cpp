#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 5000;

typedef pair<int64_t, int64_t> pair_i64;

uint64_t find_sqrt_ge(uint64_t n)
{
    if(n == 0) return 0;
    else if(n == 1) return 1;
    else if(n == 2) return 2;
    else if(n == 3) return 2;
    else if(n == 4) return 2;
    uint64_t lo = 1, hi = n;
    while(lo < hi)
    {
        uint64_t x = (lo+hi) / 2;
        if(x*x >= n)
            hi = x;
        else
            lo = x + 1;
    }
    return lo;
}

uint64_t dist(const pair_i64& a, const pair_i64& b)
{
    uint64_t dx = abs(a.first - b.first), dy = abs(a.second - b.second);
    return ceil(sqrt(dx*dx + dy*dy));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    if(n == 1) { cout << 0; return 0; }
    static array<pair_i64, MAX> points;
    for(uint32_t i = 0; i < n; i++)
        cin >> points[i].first >> points[i].second;
    static array<uint64_t, MAX> to_parent;
    to_parent[0] = 0;
    for(uint32_t v = 1; v < n; v++)
        to_parent[v] = dist(points[0], points[v]);
    for(uint32_t u = 1; u < n; u++)
    {
        for(uint32_t i = 0; i < n; i++)
            cerr << to_parent[i] << " "; cerr << endl;
        for(uint32_t v = 0; v < n; v++)
        {
            if(u == v) continue;
            to_parent[u] = min(to_parent[u], dist(points[u], points[v]));
        }
    }
        for(uint32_t i = 0; i < n; i++)
            cerr << to_parent[i] << " "; cerr << endl;
    uint64_t maxim = 0;
    for(uint32_t i = 0; i < n; i++)
        maxim = max(to_parent[i], maxim);
    cout << static_cast<uint64_t>(n - 1) * maxim;
}
