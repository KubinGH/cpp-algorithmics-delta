#include <bits/stdc++.h>

using namespace std;

const uint64_t Base = 31, Base2 = 29;
constexpr uint64_t Exp = 31, Mod = (1u << Exp) - 1;
uint64_t M(uint64_t x)
{
    x = (x >> Exp) + (x & Mod);
    x = (x >> Exp) + (x & Mod);
    return x == Mod ? 0 : x;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, q;
    cin >> n >> m >> q; n++;

    vector<vector<pair<size_t, char>>> children(n);
    for(size_t i = 1; i < n; i++)
    {
        size_t j; char c;
        cin >> j >> c;
        children[j].emplace_back(i, c);
    }

    string S;
    cin >> S;

    vector<uint64_t> H(m+1), P(m+1);
    vector<uint32_t> G(m+1), Q(m+1);
    P[0] = Q[0] = 1;
    for(size_t i = 0; i < m; i++)
    {
        P[i+1] = M(P[i] * Base);
        H[i+1] = M(H[i] * Base + uint64_t(S[i] - 'a' + 1));
        Q[i+1] = Q[i] * Base2;
        G[i+1] = G[i] * Base2 + uint32_t(S[i] - 'a' + 1);
    }

    auto sh = [&](size_t i, size_t j) {
        return M(Mod*Mod + H[j] - H[i] * P[j-i]) +
              (uint64_t(G[j] - G[i] * Q[j-i]) << 32);
    };

    map<uint64_t, size_t> haha;

    function<void(size_t, uint64_t, uint32_t)> dfs = [&](size_t u, uint64_t before, uint32_t before2) {
        for(auto [v, c] : children[u])
            dfs(v, M(before*Base + uint64_t(c - 'a' + 1)), before2*Base2 + uint32_t(c - 'a' + 1));
        haha[before + (uint64_t(before2) << 32)] = u;
    };
    dfs(0, 0, 0);

    vector<size_t> next(m+1);
    next[m] = m + 1;
    for(size_t i = 0; i < m; i++)
    {
        size_t lo = i, hi = m+1;
        while(lo < hi)
        {
            auto mid = (lo + hi) / 2;
            if(not haha.count(sh(i, mid)))
                hi = mid;
            else
                lo = mid+1;
        }
        next[i] = lo;
    }

    const size_t k = floor(sqrt(m));
    vector<size_t> NEXT(m+1);
    NEXT[m] = m+1;
    for(size_t i = 0; i < m; i++)
    {
        NEXT[i] = i;
        for(size_t j = 0; j < k and NEXT[i] <= m; j++)
            NEXT[i] = next[NEXT[i]];
    }

    while(q --> 0)
    {
        size_t i, j;
        cin >> i >> j; i--; j--;

        size_t cnt = 0, p = i;

        while(NEXT[p] <= j + 1)
            p = NEXT[p], cnt += k;
        while(next[p] <= j + 1)
            p = next[p], cnt++;

        cout << cnt << ' ' << haha[sh(p, j+1)] << '\n';
    }
}
