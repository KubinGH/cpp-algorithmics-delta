#include <bits/stdc++.h>

using namespace std;

vector<vector<uint32_t>> graph;
vector<uint32_t> inci_losers;
vector<bool> result;

inline bool win(uint32_t u) { return inci_losers[u] > 0; }

void dfs_win_root(uint32_t u, uint32_t block = -1u)
{
    for(uint32_t v : graph[u]) if(v != block)
    {
        dfs_win_root(v, u);
        if(not win(v))
            inci_losers[u]++;
    }
}

void move_root(uint32_t u, uint32_t v)
{
    if(not win(v))
        inci_losers[u]--;
    if(not win(u))
        inci_losers[v]++;
}

void dfs_solver(uint32_t u, uint32_t block = -1u)
{
    result[u] = win(u);
    for(uint32_t v : graph[u]) if(v != block)
    {
        move_root(u, v);
        dfs_solver(v, u);
        move_root(v, u);
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
    inci_losers.resize(n); result.resize(n);

    dfs_win_root(0);
    dfs_solver(0);

    for(uint32_t u = 0; u < n; u++)
        cout << (result[u] ? "Partycja\n" : "Bajtek\n");
}
