#include <bits/stdc++.h>

using namespace std;

struct disjoint_set
{
    size_t cnt;
    vector<size_t> repr, rank;
    disjoint_set(size_t n) : cnt(n), repr(n), rank(n)
    {
        iota(repr.begin(), repr.end(), 0);
    }

    size_t find(size_t u)
    {
        return repr[u] == u ? u : repr[u] = find(repr[u]);
    }

    void unite(size_t u, size_t v)
    {
        if((u = find(u)) == (v = find(v)))
            return;
        if(rank[u] > rank[v]) swap(rank[u], rank[v]);
        if(rank[u] == rank[v]) rank[v]++;
        repr[u] = v;
        cnt--;
    }
};

vector<vector<pair<size_t, uint>>> graph;
vector<size_t> parent;
vector<bool> vis, stk;

size_t watch = 0;
void dfs(size_t u)
{
    vis[u] = stk[u] = true;

    for(auto e : graph[u])
    {
        size_t v; uint i;
        tie(v, i) = e;

        if(not vis[v])
        {
            parent[v] = u;
            dfs(v);
        }
        else if(vis[v] and stk[v])
        {

        }
    }

    stk[u] = false;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<size_t>> edges(m);
    graph.resize(n+1);

    for(size_t u = 1; u <= n; u++)
        graph[0].emplace_back(u, m + 1);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v;
        graph[u].emplace_back(v, i);
        edges[i] = {u, v};
    }

    parent.resize(n+1);
    vis.resize(n+1); stk.resize(n+1);

    dfs(0);

    disjoint_set sets(n + 1);

}
