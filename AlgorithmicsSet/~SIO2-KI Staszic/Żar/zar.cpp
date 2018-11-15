#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<vector<uint32_t>> graph(n);
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<vector<uint32_t>> children(n);
    vector<uint32_t> parent(n);
    vector<bool> vis(n);
    queue<uint32_t> Q;
    parent[0] = -1u;
    Q.push(0); vis[0] = true;
    vector<uint32_t> topo;
    while(not Q.empty())
    {
        uint32_t u = Q.front(); Q.pop();
        topo.push_back(u);
        for(uint32_t v : graph[u])
        {
            if(not vis[v])
            {
                Q.push(v);
                vis[v] = true;
                parent[v] = u;
                children[u].push_back(v);
            }
        }
    }

}
