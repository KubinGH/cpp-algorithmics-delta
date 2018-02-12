#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

typedef array<vector<uint32_t>, MAX> graph_t;

pair<uint32_t, uint32_t> bfs_maxdist(graph_t& graph, uint32_t start)
{
    bool visited[MAX];
    fill(visited, visited + MAX, false);
    queue<pair<uint32_t, uint32_t> > to_visit;
    visited[start] = true;
    to_visit.emplace(start, 0);
    uint32_t maxnode = start, maxdist = 0;
    while(not to_visit.empty())
    {
        pair<uint32_t, uint32_t> current = to_visit.front();
        to_visit.pop();
        for(uint32_t n : graph[current.first])
        {
            if(not visited[n])
            {
                visited[n] = true;
                to_visit.emplace(n, current.second + 1);
                if(current.second + 1 > maxdist)
                {
                    maxnode = n;
                    maxdist = current.second + 1;
                }
            }
        }
    }
    return make_pair(maxnode, maxdist);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static graph_t graph;
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t a, b;
        cin >> a >> b; a--; b--;
        graph[a].push_back(b); graph[b].push_back(a);
    }
    uint32_t node = bfs_maxdist(graph, 0).first;
    uint32_t max_dist = bfs_maxdist(graph, node).second;
    cout << max_dist;
}
