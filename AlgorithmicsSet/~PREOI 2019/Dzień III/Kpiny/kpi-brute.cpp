#include <bits/stdc++.h>

using namespace std;

vector<vector<uint32_t>> graph;
vector<uint32_t> nimber;
vector<map<uint32_t, uint32_t>> inci_nimbers;

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

    for(uint32_t u = 0; u < n; u++)
    {
        for(uint32_t v = 0; v < n; v++)
            inci_nimbers[v].clear();
        fill(nimber.begin(), nimber.end(), 0);
        dfs_nim_root(u);
        cout << u+1 << ": ";
        for(uint32_t v = 0; v < n; v++)
            cout << nimber[v] << " "; cout << endl;
        cout << (nimber[u] ? "Partycja\n" : "Bajtek\n");
    }
}
