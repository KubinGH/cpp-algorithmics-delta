#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 200000;

struct dt { bool s, k; };

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static array<vector<uint32_t>, MAX> graph;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t a, b;
        cin >> a >> b; a--; b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    queue<uint32_t> to_visit_all;
    static array<bool, MAX> visited, status;
    for(uint32_t i = 0; i < n; i++)
        to_visit_all.push(i);
    static array<dt, MAX> check;
    while(not to_visit_all.empty())
    {
        uint32_t start = to_visit_all.front(); to_visit_all.pop();
        if(visited[start]) continue;
        queue<uint32_t> to_visit;
        to_visit.push(start);
        visited[start] = true;
        status[start] = 0;
        while(not to_visit.empty())
        {
            uint32_t current = to_visit.front();
            to_visit.pop();
            if(graph[current].empty()) goto fail;
            for(uint32_t c : graph[current])
            {
                if(not visited[c])
                {
                    to_visit.push(c);
                    visited[c] = true;
                    status[c] = status[current] == 0 ? 1 : 0;
                }
            }
        }
    }
    for(uint32_t i = 0; i < n; i++)
    {
        if(status[i] == 0) check[i].k = true;
        else if(status[i] == 1) check[i].s = true;
        for(uint32_t c : graph[i])
        {
            if(status[i] == 0) check[c].k = true;
            else if(status[i] == 1) check[c].s = true;
        }
    }
    for(uint32_t i = 0; i < n; i++)
    {
        if(not check[i].s or not check[i].k)
            goto fail;
    }
    cout << "TAK" << '\n';
    for(uint32_t i = 0; i < n; i++)
        cout << (status[i] ? 'S' : 'K') << '\n';
    return 0;
fail:
    cout << "NIE";
}
