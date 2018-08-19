#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 17;

static const char* TXT[2] = {"Ligma", "Sugma"};

int main()
{
    uint32_t n;
    cin >> n;
    static vector<uint32_t> graph[MAX];
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    static uint32_t dist[2][MAX];
    for(uint32_t i = 0; i < 2; i++)
    {
        queue<uint32_t> Q;
        static bitset<MAX> vis; vis.reset();
        fill(begin(dist[i]), begin(dist[i]) + n, -1u);
        Q.push(i ? n - 1 : 0);
        dist[i][Q.front()] = 0; vis[Q.front()] = true;
        while(not Q.empty())
        {
            uint32_t u = Q.front(); Q.pop();
            for(uint32_t v : graph[u])
            {
                if(not vis[v] and v != (i ? 0 : n - 1))
                {
                    vis[v] = true;
                    dist[i][v] = dist[i][u] + 1;
                    Q.push(v);
                }
            }
        }
    }
    uint32_t g[2] = {0, 0};
    for(uint32_t i = 0; i < n; i++)
    {
        if(dist[0][i] <= dist[1][i])
            g[0]++;
        else
            g[1]++;
    }
    if(g[0] > g[1])
        cout << TXT[0];
    else
        cout << TXT[1];
}
