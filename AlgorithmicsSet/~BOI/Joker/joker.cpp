#include <bits/stdc++.h>

using namespace std;

struct dsu_bipartite
{
    vector<size_t> repr;
    vector<char> rank;
    bool ok;

    void reset()
    {
        fill(rank.begin(), rank.end(), 0);
        for(size_t i = 0; i < repr.size(); i++)
            repr[i] = i;
        ok = true;
    }

    dsu_bipartite(size_t n) : repr(2*n+2), rank(2*n+2) { reset(); }

    size_t find(size_t u)
    {
        return u == repr[u] ? u : repr[u] = find(repr[u]);
    }

    bool unite(size_t u, size_t v)
    {
        u++; v++;

        u = find(2*u); v = find(2*v);
        if(u/2 == v/2)
        {
            ok &= u ^ v;
            return false;
        }
        repr[u^0] = v^1;
        repr[u^1] = v^0;
        return true;
    }
};

struct query { size_t l, r, i; };

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, q;
    cin >> n >> m >> q;

    vector<pair<size_t, size_t>> edges(m);
    for(auto& [u, v] : edges)
        cin >> u >> v, u--, v--;

    edges.resize(2*m);
    copy(edges.begin(), edges.begin() + m, edges.begin() + m);

    vector<bool> answer(q);
    vector<query> queries(q);
    for(auto& [l, r, i] : queries)
        cin >> l >> r, tie(l, r) = make_pair(r, m+l-1);

    for(size_t i = 0; i < q; i++)
        queries[i].i = i;

    sort(queries.begin(), queries.end(), [&](const auto& lhs, const auto& rhs) {
        return lhs.r < rhs.r or (lhs.r == rhs.r and lhs.l > rhs.l);
    });

    size_t curr_l = SIZE_MAX, curr_r = SIZE_MAX;
    dsu_bipartite sets(n);
    for(auto [l, r, j] : queries)
    {
        if(r != curr_r)
        {
            sets.reset();
            curr_l = curr_r = r;

        }

        while(sets.ok and curr_l > l)
            curr_l--, sets.unite(edges[curr_l].first, edges[curr_l].second);

        answer[j] = not sets.ok;
    }

    for(size_t i = 0; i < q; i++)
        cout << (answer[i] ? "YES\n" : "NO\n");
}
