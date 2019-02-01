#include <bits/stdc++.h>

using namespace std;

vector<vector<uint32_t>> graph;
vector<uint32_t> nimber;
vector<map<uint32_t, uint32_t>> inci_nimbers;
vector<bool> result;
vector<pair<uint32_t, uint32_t>> extends;

uint32_t mex(const map<uint32_t, uint32_t>& v)
{
    uint32_t i = 0;
    for(auto it = v.begin(); it != v.end(); it++, i++)
        if(it->first != i or not it->second)
            return i;
    return i;
}

void dfs_nim_root(uint32_t u, uint32_t block = -1u)
{
    for(uint32_t v : graph[u]) if(v != block)
    {
        dfs_nim_root(v, u);
        inci_nimbers[u][nimber[v]]++;
    }
    nimber[u] = mex(inci_nimbers[u]);
    uint32_t i = nimber[u]+1;
    bool done = false;
    for(auto it = inci_nimbers[u].upper_bound(nimber[u]); it != inci_nimbers[u].end(); it++)
        if(i != it->first or not it->second)
            { extends[u] = {nimber[u], i}; done = true; break; }
    if(not done)
        extends[u] = {nimber[u], i};
}

void move_root(uint32_t u, uint32_t v)
{
    inci_nimbers[v][nimber[u]]--;
    inci_nimbers[u][nimber[v]]--;
    if(nimber[u] > nimber[v] and inci_nimbers[u][nimber[v]] == 0)
        nimber[u] = nimber[v];
    if(nimber[u] == extends[v].first)
        nimber[v] = extends[v].second;
    inci_nimbers[v][nimber[u]]++;
    inci_nimbers[u][nimber[v]]++;
}

void dfs_solver(uint32_t u, uint32_t block = -1u)
{
    result[u] = (nimber[u] > 0);
    for(uint32_t v : graph[u]) if(v != block)
    {
        uint32_t n1 = nimber[u], n2 = nimber[v];
        move_root(u, v);
        dfs_solver(v, u);
        inci_nimbers[u][nimber[v]]--; inci_nimbers[v][nimber[u]]--;
        inci_nimbers[u][nimber[v] = n2]++; inci_nimbers[v][nimber[u] = n1]++;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    graph.resize(n);
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    nimber.resize(n); inci_nimbers.resize(n);
    result.resize(n); extends.resize(n);
    fill(nimber.begin(), nimber.end(), 0);

    dfs_nim_root(0);
    dfs_solver(0);

    for(uint32_t u = 0; u < n; u++)
        cout << (result[u] ? "Partycja\n" : "Bajtek\n");
}
