#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t cities;
    cin >> cities;
    static array<vector<uint32_t>, MAX> next_to;
    for(uint32_t i = 0; i < cities - 1; i++)
    {
        uint32_t a, b;
        cin >> a >> b; a--; b--;
        next_to[a].push_back(b);
        next_to[b].push_back(a);
    }
    static array<uint32_t, MAX> parent, active_children;
    static array<bool, MAX> active;
    fill(active.begin(), active.begin() + cities, true);
    queue<uint32_t> to_visit;
    static array<bool, MAX> visited;
    to_visit.push(0);
    visited[0] = true;
    parent[0] = MAX;
    while(not to_visit.empty())
    {
        uint32_t current = to_visit.front(); to_visit.pop();
        for(uint32_t nxt : next_to[current])
        {
            if(not visited[nxt])
            {
                parent[nxt] = current;
                active_children[current]++;
                visited[nxt] = true;
                to_visit.push(nxt);
            }
        }
    }
    uint32_t scount;
    cin >> scount;
    uint32_t groups = 1;
    for(uint32_t s = 0; s < scount; s++)
    {
        int32_t iz;
        cin >> iz;
        uint32_t z = abs(iz) - 1;
        if(iz > 0)
        {
            active[z] = false;
            if(z != 0)
            {
                active_children[parent[z]]--;
                groups += active_children[z] + active[parent[z]] - 1;
            }
            else
                groups += active_children[z] - 1;
        }
        else
        {
            active[z] = true;
            if(z != 0)
            {
                active_children[parent[z]]++;
                groups -= active_children[z] + active[parent[z]] - 1;
            }
            else
                groups -= active_children[z] - 1;
        }
        cout << groups << '\n';
    }
}
