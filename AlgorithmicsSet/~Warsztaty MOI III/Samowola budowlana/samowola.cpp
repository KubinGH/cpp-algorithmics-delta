#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e5;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static vector<pair<uint32_t, uint32_t>> graph[MAX];
    static pair<uint32_t, uint32_t> edges[MAX];
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        edges[i].first = u; edges[i].second = v;
        graph[u].emplace_back(v, i);
        graph[v].emplace_back(u, i);
    }
    static bitset<MAX> visited, used_edge;
    stack<uint32_t> to_visit;
    visited[0] = true; to_visit.push(0);
    uint32_t unused_edges = m;
    while(not to_visit.empty())
    {
        uint32_t u = to_visit.top(); to_visit.pop();
        //cerr << " @ " << u+1 << endl;
        for(auto e : graph[u])
        {
            uint32_t v, ei;
            tie(v, ei) = e;
            if(not visited[v])
            {
                visited[v] = true;
                to_visit.push(v);
                used_edge[ei] = true;
                //cerr << "use " << edges[ei].first+1 << " " << edges[ei].second+1 << endl;
                unused_edges--;
            }
        }
    }
    cout << unused_edges << "\n";
    for(uint32_t i = 0; i < m; i++)
        if(not used_edge[i])
            cout << edges[i].first+1 << " " << edges[i].second+1 << "\n";
}
