#include <bits/stdc++.h>

using namespace std;

struct dsu_bipartite
{
    vector<size_t> repr;
    vector<vector<size_t>> members;
    vector<bool> color;
    bool ok = true;

    dsu_bipartite(size_t n) : repr(n), members(n), color(n)
    {
        for(size_t i = 0; i < n; i++)
            repr[i] = i, members[i].push_back(i);
    }

    bool unite(size_t u, size_t v)
    {
        if(repr[u] == repr[v])
        {
            if(color[u] == color[v])
                ok = false;
            return false;
        }
        bool x = (color[u] == color[v]);
        u = repr[u]; v = repr[v];

        if(members[u].size() > members[v].size())
            swap(u, v);
        for(auto w : members[u])
            repr[w] = v, members[v].push_back(w), color[w] = color[w] ^ x;
        members[u].clear();
        members[u].shrink_to_fit();

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
    dsu_bipartite sets(0);
    for(auto [l, r, j] : queries)
    {
        cout << l << ".." << r << endl;
        if(r != curr_r)
        {
            sets = dsu_bipartite(n);
            curr_l = curr_r = r;
        }

        while(curr_l > l)
            curr_l--, sets.unite(edges[curr_l].first, edges[curr_l].second);

        answer[j] = not sets.ok;
    }

    for(size_t i = 0; i < q; i++)
        cout << (answer[i] ? "YES\n" : "NO\n");
}
