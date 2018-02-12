#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t nodes, edges;
    cin >> nodes >> edges;
    static array<vector<uint32_t>, MAX> graph;
    for(uint32_t i = 0; i < edges; i++)
    {
        uint32_t a, b;
        cin >> a >> b; a--; b--;
        graph[a].push_back(b); graph[b].push_back(a);
    }
    static array<bool, MAX> visited;
    queue<uint32_t> to_visit;
    to_visit.push(0);
    visited[0] = true;
    while(not to_visit.empty())
    {
        uint32_t current = to_visit.front(); to_visit.pop();
        for(uint32_t node : graph[current])
        {
            if(not visited[node])
            {
                visited[node] = true;
                to_visit.push(node);
            }
        }
    }
    for(uint32_t i = 0; i < nodes; i++)
        cout << (visited[i] ? "TAK\n" : "NIE\n");

}
