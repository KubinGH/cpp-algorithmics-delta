#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint64_t, MAX> weights;
    for(uint32_t i = 0; i < n; i++)
        cin >> weights[i];
    static array<vector<uint32_t>, MAX> graph;
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    static bitset<MAX> visited;
    stack<pair<uint32_t, uint64_t>> to_visit;
    visited[0] = true; to_visit.emplace(0, weights[0]);
    uint64_t best = weights[0];
    while(not to_visit.empty())
    {
        uint32_t u = to_visit.top().first;
        uint64_t c = to_visit.top().second;
        to_visit.pop();
        best = max(best, c);
        for(uint32_t v : graph[u])
        {
            if(not visited[v])
            {
                visited[v] = true;
                to_visit.emplace(v, c + weights[v]);
            }
        }
    }
    cout << best;
}
