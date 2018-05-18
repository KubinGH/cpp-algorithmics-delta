#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e5;
const uint64_t MOD = 1e9 + 7;

int main()
{
    uint32_t n;
    cin >> n;
    static vector<pair<uint32_t, uint64_t>> graph[MAX];
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t a, b; uint64_t w;
        cin >> a >> b >> w; a--; b--;
        graph[a].emplace_back(b, w);
        graph[b].emplace_back(a, w);
    }
    uint32_t root = 0;
    //for(uint32_t i = 0; i < n; i++)
    //    if(graph[i].size() == 1)
    //        { root = i; break; }
    static uint32_t parent[MAX];
    static uint64_t parent_cost[MAX];
    static vector<uint32_t> children[MAX];
    static bitset<MAX> visited;
    stack<uint32_t> to_visit;
    vector<uint32_t> topological;
    visited[root] = true; to_visit.push(root);
    while(not to_visit.empty())
    {
        uint32_t u = to_visit.top(); to_visit.pop();
        topological.push_back(u);
        for(auto e : graph[u])
        {
            uint32_t v; uint64_t w;
            tie(v, w) = e;
            if(not visited[v])
            {
                parent[v] = u; parent_cost[v] = w;
                children[u].push_back(v);
                visited[v] = true; to_visit.push(v);
            }
        }
    }
    if(parent[0]) {}
    static uint64_t vertex_result[MAX];
    uint64_t result = 0;
    reverse(topological.begin(), topological.end());
    for(uint32_t u : topological)
    {
    }
    cout << result;
}
