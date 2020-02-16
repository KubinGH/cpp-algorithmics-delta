#include <bits/stdc++.h>

using namespace std;

const uint32_t Base = 37;

const uint32_t K = 31; const uint64_t Mod = (1u << 31) - 1;

uint32_t M(uint64_t x)
{
    x = (x >> K) + (x & Mod);
    x = (x >> K) + (x & Mod);
    return x;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    uint32_t n, k, q;
    cin >> n >> k >> q;

    vector<uint64_t> Pow1(k), Pow2(k);
    Pow1[0] = 1; Pow2[0] = 1;
    for(uint32_t i = 1; i < k; i++)
        Pow1[i] = M(Pow1[i-1] * Base), Pow2[i] = Pow2[i-1] * Base;

    vector<string> P(n);
    for(uint32_t i = 0; i < n; i++)
        P[i].reserve(k), cin >> P[i];

    using rhash = pair<uint32_t, uint64_t>;
    vector<rhash> H(n);
    auto val = [&](uint32_t i, char c) {
        return rhash{M(Pow1[i] * (c - 'a' + 1)), Pow2[i] * (c - 'a' + 1)};
    };
    auto push = [&](uint32_t p, uint32_t i, char c) {
        auto v = val(i, c);
        H[p].first += v.first; H[p].second += v.second;
    };
    auto pop = [&](uint32_t p, uint32_t i, char c) {
        auto v = val(i, c);
        H[p].first -= v.first; H[p].second -= v.second;
    };
    for(uint32_t p = 0; p < n; p++)
        for(uint32_t i = 0; i < k; i++)
            push(p, i, P[p][i]);

    map<rhash, set<uint32_t>> occ;
    for(uint32_t p = 0; p < n; p++)
        occ[H[p]].insert(p);
    vector<uint32_t> best(n);
    for(uint32_t p = 0; p < n; p++)
        best[p] = occ[H[p]].size();

    while(q --> 0)
    {
        uint32_t p1, i1, p2, i2;
        cin >> p1 >> i1 >> p2 >> i2; p1--; i1--; p2--; i2--;
        occ[H[p1]].erase(p1); occ[H[p2]].erase(p2);
        pop(p1, i1, P[p1][i1]); pop(p2, i2, P[p2][i2]);
        swap(P[p1][i1], P[p2][i2]);
        push(p1, i1, P[p1][i1]); push(p2, i2, P[p2][i2]);
        occ[H[p1]].insert(p1); occ[H[p2]].insert(p2);
        uint32_t o1 = occ[H[p1]].size(), o2 = occ[H[p2]].size();
        for(uint32_t p : occ[H[p1]])
            best[p] = max(best[p], o1);
        for(uint32_t p : occ[H[p2]])
            best[p] = max(best[p], o2);
    }
    for(uint32_t p = 0; p < n; p++)
        cout << best[p] << "\n";
}
