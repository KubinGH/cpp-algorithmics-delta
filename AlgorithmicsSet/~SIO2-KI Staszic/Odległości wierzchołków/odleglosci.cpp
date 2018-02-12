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
    static array<uint32_t, MAX> dist;
    fill(dist.begin(), dist.begin() + nodes, MAX);
    static array<bool, MAX> visited;
    queue<pair<uint32_t, uint32_t> > to_visit;
    dist[0] = 0;
    visited[0] = true;
    to_visit.emplace(0, 0);
    while(not to_visit.empty())
    {
        pair<uint32_t, uint32_t> current = to_visit.front();
        to_visit.pop();
        for(uint32_t n : graph[current.first])
        {
            if(not visited[n])
            {
                dist[n] = current.second + 1;
                visited[n] = true;
                to_visit.emplace(n, dist[n]);
            }
        }
    }
    for(uint32_t i = 0; i < nodes; i++)
        cout << (dist[i] == MAX ? -1 : (int)dist[i]) << "\n";
}
