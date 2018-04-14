#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e6;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static array<vector<pair<uint32_t, uint32_t>>, MAX> graph;
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v, c;
        cin >> u >> v >> c; u--; v--;
        graph[u].emplace_back(v, c);
        graph[v].emplace_back(u, c);
    }
    static array<bool, MAX> is_goal;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u;
        cin >> u; u--;
        is_goal[u] = true;
    }
    static array<uint32_t, MAX> parent, parent_cost;
    static bitset<MAX> visited;
    static array<vector<uint32_t>, MAX> children;
    queue<uint32_t> to_visit;
    static array<uint32_t, MAX> topological; uint32_t pi = 0;
    to_visit.push(0);
    visited[0] = true;
    while(not to_visit.empty())
    {
        uint32_t u = to_visit.front(); to_visit.pop();
        //cerr << u+1 << " ";
        topological[pi] = u; pi++;
        for(pair<uint32_t, uint32_t> p : graph[u])
        {
            uint32_t v, c;
            tie(v, c) = p;
            if(not visited[v])
            {
                parent[v] = u;
                parent_cost[v] = c;
                children[u].push_back(v);
                visited[v] = true;
                to_visit.push(v);
            }
        }
    }
    //cerr << endl;
    reverse(topological.begin(), topological.begin() + n);
    static array<uint32_t, MAX> goals;
    static array<uint64_t, MAX> result;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t u = topological[i];
        if(is_goal[u])
            goals[u]++;
        for(uint32_t v : children[u])
        {
            if(goals[v])
            {
                result[u] += result[v] + 2 * parent_cost[v];
                goals[u] += goals[v];
            }
        }
        //cerr << u+1 << ": " << result[u] << endl;
    }
    //cerr << endl;
    cout << result[0];
}
