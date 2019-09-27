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

    vector<size_t> requests(n), distance(n);
    vector<bool> visited(n);
    queue<size_t> to_visit;
    to_visit.push(0);

    size_t result = 0, result2 = 0;
    while(not to_visit.empty())
    {
        size_t u = to_visit.front(); to_visit.pop();
        if(requests[u] > 1)
            result += requests[u];
        visited[u] = true;
        for(auto v : graph[u])
        {
            if(not visited[v])
            {
                if(not requests[v])
                    distance[v] = distance[u] + 1, to_visit.push(v);
                if(distance[v] == distance[u] + 1)
                    requests[v]++;
            }
            if(distance[u] == distance[v])
                result2++;
        }
    }

    size_t unvisited_edges = 0;
    for(size_t u = 0; u < n; u++)
        if(not visited[u])
            unvisited_edges += graph[u].size();

    cout << result + result2/2 + unvisited_edges/2;
}
