#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<size_t>> graph(n);
    vector<int> balance(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        balance[u]++; balance[v]--;
    }

    size_t odds = 0;
    for(size_t u = 0; u < n; u++)
        odds += balance[u] != 0;

    if(odds != 2 or balance[0] != 1 or balance[n-1] != -1)
    {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    vector<size_t> tovis = {0}, circuit;
    while(not tovis.empty())
    {
        auto u = tovis.back();
        if(not graph[u].empty())
            tovis.push_back(graph[u].back()), graph[u].pop_back();
        else
            circuit.push_back(u), tovis.pop_back();
    }
    reverse(circuit.begin(), circuit.end());

    if(circuit.size() < m + 1)
    {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    for(auto u : circuit)
        cout << u+1 << ' ';
    cout << endl;
}
