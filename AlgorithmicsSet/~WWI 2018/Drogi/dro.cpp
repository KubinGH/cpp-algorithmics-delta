#include <bits/stdc++.h>

using namespace std;

struct edge { uint32_t u, v; };

struct disjoint_set
{
    uint32_t n;
    vector<uint32_t> parent, degree;
    disjoint_set(uint32_t _n) : n(_n), parent(n), degree(n)
        { iota(parent.begin(), parent.end(), 0); }
    uint32_t find(uint32_t v)
        { return v == parent[v] ? v : parent[v] = find(parent[v]); }
    void unite(uint32_t u, uint32_t v)
    {
        u = find(u); v = find(v);
        if(degree[u] > degree[v]) swap(u, v);
        if(degree[u] == degree[v]) degree[v]++;
        parent[u] = v;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m, k;
    cin >> n >> m >> k;
    vector<edge> unused[2], used[2];
    for(uint32_t w = 0; w < 2; w++)
        unused[w].reserve(m), used[w].reserve(m);
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t u, v, w;
        cin >> u >> v >> w;
        unused[w].push_back({u, v});
    }
    disjoint_set dset(n);
    for(uint32_t w : {0, 1})
    {
        for(uint32_t i = unused[w].size(), u, v; i --> 0; )
        {
            if(dset.find(u = unused[w][i].u) != dset.find(v = unused[w][i].v))
            {
                dset.unite(u, v);
                used[w].push_back(unused[w][i]);
                swap(unused[w][i], unused[w].back());
                unused[w].pop_back();
            }
        }
    }
    if(used[0].size() + used[1].size() < n - 1 or
       used[0].size() > k)
    {
        cout << "NIE";
        return 0;
    }

    vector<vector<uint32_t>> tree(n);
    for(uint32_t w = 0; w < 2; w++)
        for(auto e : used[w])
            tree[e.u].push_back(e.v), tree[e.v].push_back(e.u);

    for(auto e : unused[1])
    {

    }

    if(used[0].size() > k)
        cout << "NIE";
    else
    {
        cout << "TAK\n";
        for(uint32_t w = 0; w < 2; w++)
            for(auto e : used[w])
                cout << e.u << " " << e.v << " " << w << "\n";
    }

}
