#include <bits/stdc++.h>

using namespace std;

struct edge_t { size_t u, v; bool used; };

size_t nd(const edge_t& e, size_t u) { return e.u == u ? e.v : e.u; }

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<size_t>> graph(n);
    vector<edge_t> edges(m);
    for(size_t i = 0; i < m; i++)
    {
        cin >> edges[i].u >> edges[i].v;
        edges[i].u--; edges[i].v--;
        graph[edges[i].u].push_back(i);
        graph[edges[i].v].push_back(i);
    }

    size_t sum_deg = 0;
    vector<bool> vis(n);
    function<void(size_t)> dfs_check = [&](size_t u) {
        if(vis[u]) return;
        vis[u] = true;
        for(const auto& e : graph[u])
            dfs_check(nd(edges[e], u));
        sum_deg += graph[u].size() / 2;
    };
    dfs_check(0);

    if(sum_deg != m)
    {
        cout << "NIE";
        return 0;
    }

    stack<size_t> S; S.push(0);
    vector<size_t> C;

    while(not S.empty())
    {
        size_t u = S.top(), i;
        while(not graph[u].empty() and edges[i = graph[u].back()].used)
            graph[u].pop_back();

        if(graph[u].empty())
        {
            C.push_back(u);
            S.pop();
        }
        else
        {
            edges[i].used = true;
            S.push(nd(edges[i], u));
        }
    }

    cout << "TAK\n";
    for(auto u : C)
        cout << u+1 << ' ';
}
