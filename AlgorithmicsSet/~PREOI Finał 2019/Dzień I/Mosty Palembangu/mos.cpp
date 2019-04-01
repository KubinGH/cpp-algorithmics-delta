#include <bits/stdc++.h>

using namespace std;

struct gather_t { uint64_t forced; vector<pair<uint32_t, uint32_t>> pos; };

uint32_t abs_diff(uint32_t a, uint32_t b) { return a > b ? a - b : b - a; }

gather_t gather(uint32_t n)
{
    gather_t G = {0, {}};
    G.pos.reserve(n);
    for(uint32_t i = 0; i < n; i++)
    {
        char p, q; uint32_t s, t;
        cin >> p >> s >> q >> t;
        if(s > t)
            tie(s, t) = make_pair(t, s);
        G.forced += t - s;
        if(p != q)
            G.pos.emplace_back(s, t), G.forced++;
    }
    return G;
}

template<typename Arg, typename MonoOperation>
uint32_t bitonic_minimum(Arg lo, Arg hi, MonoOperation F)
{
    while(lo < hi)
    {
        Arg mid = (lo + hi) / 2;
        if(F(mid) < F(mid+1))
            hi = mid;
        else
            lo = mid+1;
    }
    return lo;
}

uint64_t solve_case1(const vector<pair<uint32_t, uint32_t>>& pos)
{
    auto D = [&](uint32_t m) {
        uint64_t r = 0;
        for(auto p : pos)
        {
            uint32_t s, t; tie(s, t) = p;
            if(not (s <= m and m <= t))
                r += (uint64_t)2 * min(abs_diff(m, s), abs_diff(t, m));
        }
        return r;
    };
    return D(bitonic_minimum(0u, (1u<<30), D));
}

uint64_t solve_case2(const vector<pair<uint32_t, uint32_t>>& pos)
{
    auto d = [&](uint32_t s, uint32_t t, uint32_t m) {
        if(not (s <= m and m <= t))
            return 2 * min(abs_diff(m, s), abs_diff(t, m));
        else
            return 0u;
    };
    auto DD = [&](uint32_t M) {
        auto D = [&](uint32_t m) {
            uint64_t r = 0;
            for(auto p : pos)
            {
                uint32_t s, t; tie(s, t) = p;
                if(not ((M <= s and s <= m) or (M <= t and t <= m)))
                    r += min(d(s, t, M), d(s, t, m));
            }
            return r;
        };
        return D(bitonic_minimum(M+1, (1u<<30), D));
    };
    return DD(bitonic_minimum(0u, (1u<<30), DD));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t k, n;
    cin >> k >> n;
    auto G = gather(n);
    if(k == 1)
        cout << G.forced + solve_case1(G.pos);
    else if(k == 2)
        cout << G.forced + solve_case2(G.pos);
}
