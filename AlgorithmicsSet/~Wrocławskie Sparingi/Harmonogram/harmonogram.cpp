#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 200000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    uint32_t start, target;
    cin >> start >> target; start--; target--;
    static array<vector<uint32_t>, MAX> dependants, required;
    static array<uint32_t, MAX> dependant_count, required_count;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        dependants[u].push_back(v);
        dependant_count[u]++;
        required[v].push_back(u);
        required_count[v]++;
    }
    static array<bool, MAX> visited;
    queue<uint32_t> to_visit;
    to_visit.push(start);
    visited[start] = true;
    while(not to_visit.empty())
    {
        uint32_t u = to_visit.front(); to_visit.pop();
        for(uint32_t v : dependants[u])
            required_count[v]--, dependant_count[u]--;
        for(uint32_t v : required[u])
        {
            if(not visited[v])
            {
                visited[v] = true;
                to_visit.push(v);
            }
        }
    }
    visited[target] = true;
    for(uint32_t i = 0; i < n; i++)
    {
        if(required_count[i] == 0 and not visited[i])
        {
            to_visit.push(i);
            visited[i] = true;
        }
    }
    uint32_t result = 0;
    while(not to_visit.empty())
    {
        uint32_t u = to_visit.front(); to_visit.pop();
        for(uint32_t v : dependants[u])
        {
            if(not visited[v])
            {
                required_count[v]--;
                dependant_count[u]--;
                if(required_count[v] == 0)
                {
                    visited[v] = true;
                    to_visit.push(v);
                }
            }
        }
        result++;
    }
    cout << result;
}
