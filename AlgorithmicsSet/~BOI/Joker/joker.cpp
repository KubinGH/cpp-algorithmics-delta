#include <bits/stdc++.h>

using namespace std;

struct dsu_bipartite
{
    vector<size_t> repr, rank;
    vector<pair<size_t, size_t>> history;
    bool ok;

    void reset()
    {
        for(size_t i = 0; i < repr.size(); i++)
            repr[i] = i;
        history.clear();
        ok = true;
    }

    dsu_bipartite(size_t n) : repr(2*n+2), rank(n+1)
    {
        iota(rank.begin(), rank.end(), 0);
        shuffle(rank.begin(), rank.end(), mt19937(1337));
        reset();
    }

    size_t find(size_t u)
    {
        return u == repr[u] ? u : find(repr[u]);
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
        if(rank[u/2] > rank[v/2]) swap(u, v);
        history.emplace_back(u, v);
        repr[u^0] = v^1;
        repr[u^1] = v^0;
        return true;
    }

    void rollback(size_t k = 1)
    {
        while(k --> 0)
        {
            auto [u, v] = history.back();
            history.pop_back();
            repr[u^0] = u^0; repr[u^1] = u^1;
        }
    }
};


void divida_et_impera(
    size_t a, size_t b, size_t c, size_t d,
    dsu_bipartite& desu, vector<size_t>& stop,
    const vector<pair<size_t, size_t>>& edges)
{
    if(a >= b)
        return;

    size_t i = (a + b) / 2, &j = stop[i];
    size_t e = 0; bool pok = desu.ok;

    auto unite = [&](size_t k) {
        e += desu.unite(edges[k].first, edges[k].second);
    };
    auto back = [&]() {
        desu.rollback(e); e = 0;
        desu.ok = pok;
    };

    j = i;
    while(j < d and desu.ok)
    {
        unite(j++);
        if(b < c and j == b)
            j = c;
    }
    j = max(j, c);
    back();

    for(size_t k = i; k < min(b, c); k++)
        unite(k);
    divida_et_impera(a, i, c, min(j+1, d), desu, stop, edges);
    back();

    for(size_t k = max(b, c); k < j; k++)
        unite(k);
    divida_et_impera(i+1, b, j, d, desu, stop, edges);
    back();
}

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

    vector<size_t> stop(2*m);
    dsu_bipartite desu(n);
    divida_et_impera(0, 2*m, 0, 2*m, desu, stop, edges);

    while(q --> 0)
    {
        size_t l, r;
        cin >> l >> r;
        tie(l, r) = make_pair(r, m+l-1);
        cout << (r >= stop[l] ? "YES" : "NO") << '\n';
    }
}
