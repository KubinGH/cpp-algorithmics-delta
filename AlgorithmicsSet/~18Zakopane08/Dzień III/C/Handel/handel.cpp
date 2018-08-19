#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 18;

void distances(const vector<uint32_t> (&graph)[MAX], uint32_t s,
               uint32_t (&dist)[MAX])
{
    stack<uint32_t> to_visit;
    static bitset<MAX> visited; visited.reset();
    to_visit.push(s); visited[s] = true;
    dist[s] = 0;
    while(not to_visit.empty())
    {
        uint32_t u = to_visit.top(); to_visit.pop();
        for(uint32_t v : graph[u])
        {
            if(not visited[v])
            {
                to_visit.push(v); visited[v] = true;
                dist[v] = dist[u] + 1;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static vector<uint32_t> graph[MAX];
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<uint32_t> marked;
    for(uint32_t u = 0; u < n; u++)
    {
        if(graph[u].size() >= 3)
            marked.push_back(u);
    }
    static uint32_t dist[2][MAX];
    distances(graph, marked[0], dist[0]);
    uint32_t p = marked[0];
    for(uint32_t u : marked)
        if(dist[0][u] > dist[0][p])
            p = u;
    distances(graph, p, dist[1]);
    uint32_t result = 0;
    for(uint32_t u : marked)
        result = max(result, dist[1][u]);
    cout << result;
}
