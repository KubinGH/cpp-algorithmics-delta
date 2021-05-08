#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<pair<size_t, size_t>>> graph(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].emplace_back(v, i);
        graph[v].emplace_back(u, i);
    }
    for(size_t i = 0; i < n; i++)
      if(graph[i].size() % 2)
    {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    vector<bool> use(m);
    vector<size_t> tovis = {0}, circuit;
    while(not tovis.empty())
    {
        auto u = tovis.back();
        while(not graph[u].empty() and use[graph[u].back().second])
            graph[u].pop_back();
        if(not graph[u].empty())
            use[graph[u].back().second] = true, tovis.push_back(graph[u].back().first);
        else
            circuit.push_back(u), tovis.pop_back();
    }

    if(accumulate(use.begin(), use.end(), 0u) < m)
    {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    for(auto u : circuit)
        cout << u+1 << ' ';
    cout << endl;
}
