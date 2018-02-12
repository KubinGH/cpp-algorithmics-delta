#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;
const uint32_t INF = numeric_limits<uint32_t>::max();

int main()
{
    ios_base::sync_with_stdio(false); cout.tie(0); cin.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static array<vector<pair<uint32_t, uint32_t> >, MAX> graph;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        graph[a].emplace_back(b, c);
        graph[b].emplace_back(a, c);
    }
    static array<uint32_t, MAX> distance;
    static array<vector<uint32_t>, MAX> previous;
    priority_queue<pair<uint32_t, uint32_t>,
                   vector<pair<uint32_t, uint32_t> >,
                   greater<pair<uint32_t, uint32_t> > > Q;
    for(uint32_t i = 0; i < n; i++)
        distance[i] = INF;
    distance[0] = 0;
    Q.emplace(0, 0);
    while(not Q.empty())
    {
        pair<uint32_t, uint32_t> cpair = Q.top(); Q.pop();
        uint32_t cdist = cpair.first, cnode = cpair.second;
        if(cdist > distance[cnode]) continue;
        for(pair<uint32_t, uint32_t> npair : graph[cnode])
        {
            uint32_t node = npair.first, dist = npair.second;
            if(cdist + dist < distance[node])
            {
                distance[node] = cdist + dist;
                previous[node].clear();
                previous[node].push_back(cnode);
                Q.emplace(distance[node], node);
            }
            else if(cdist + dist == distance[node])
            {
                previous[node].push_back(cnode);
            }
        }
    }
    static array<bool, MAX> in_path;
    set<uint32_t> result;
    result.insert(0); result.insert(n - 1);
    in_path[0] = in_path[n - 1] = true;
    stack<uint32_t> trav;
    trav.push(n - 1);
    while(not trav.empty())
    {
        uint32_t current = trav.top(); trav.pop();
        for(uint32_t node : previous[current])
        {
            if(not in_path[node])
            {
                result.insert(node);
                trav.push(node);
                in_path[node] = true;
            }
        }
    }
    for(uint32_t node : result)
        cout << node + 1 << '\n';
}
