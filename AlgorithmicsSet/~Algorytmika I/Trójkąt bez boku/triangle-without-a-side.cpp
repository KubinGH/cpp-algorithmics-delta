#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<size_t>> graph(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for(size_t u = 0; u < n; u++)
        sort(graph[u].begin(), graph[u].end());

    for(size_t b = 0; b < n; b++)
    {
        for(auto a : graph[b])
            for(auto c : graph[b])
                if(a != c and not binary_search(graph[a].begin(), graph[a].end(), c))
        {
            cout << "TAK\n" << a+1 << " " << b+1 << " " << c+1;
            return 0;
        }
    }

    cout << "NIE";
}
