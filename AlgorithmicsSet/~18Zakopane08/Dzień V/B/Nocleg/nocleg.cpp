#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 17, LOG_MAX = 17;

uint32_t JP[MAX][LOG_MAX], depth[MAX];

uint32_t lca(uint32_t u, uint32_t v)
{
    if(depth[u] < depth[v])
        swap(u, v);
    for(uint32_t j = LOG_MAX; j --> 0; )
        if(depth[u] >= depth[v] + (1 << j))
            u = JP[u][j];
    if(u == v) return u;
    for(uint32_t j = LOG_MAX; j --> 0; )
        if(depth[u] > (1u << j) and JP[u][j] != JP[v][j])
            u = JP[u][j], v = JP[v][j];
    return JP[v][0];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, t;
    cin >> n >> t;
    static vector<uint32_t> graph[MAX];
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    // global uint32_t JP[MAX][LOG_MAX], depth[MAX];
    for(uint32_t i = 0; i < n; i++) for(uint32_t j = 0; j < LOG_MAX; j++)
        JP[i][j] = -1u;
    static bitset<MAX> vis;
    stack<uint32_t> Q; Q.push(0); vis[0] = true;
    while(not Q.empty())
    {
        uint32_t u = Q.top(); Q.pop();
        for(uint32_t v : graph[u])
        {
            if(not vis[v])
            {
                Q.push(v); vis[v] = true; depth[v] = depth[u] + 1;
                JP[v][0] = u;
                for(uint32_t i = 1; i < LOG_MAX and JP[v][i-1] != -1u; i++)
                {
                    uint32_t m = JP[v][i-1];
                    JP[v][i] = JP[m][i-1];
                }
            }
        }
    }
    while(t --> 0)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        uint32_t a = lca(u, v);
        if((depth[u] + depth[v]) % 2 == 1)
            { cout << "NIE\n"; continue; }
        else if(depth[u] < depth[v])
            swap(u, v);
        uint32_t x = (depth[u] + depth[v] - 2*depth[a]) / 2;
        uint32_t w = u;
        for(uint32_t j = LOG_MAX; j --> 0;)
        {
            if(x >= (1u << j))
                w = JP[w][j], x -= (1 << j);
        }
        cout << w+1 << "\n";
    }
}
