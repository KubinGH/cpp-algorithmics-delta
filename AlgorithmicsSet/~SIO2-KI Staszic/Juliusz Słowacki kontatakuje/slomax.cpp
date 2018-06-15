#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 5e5, MAXLOG = 19;
const int32_t INF_I32 = numeric_limits<int32_t>::max();

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    uint32_t logn = 32 - __builtin_clz(n);
    static vector<pair<uint32_t, int32_t>> graph[MAX];
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v; int32_t w;
        cin >> u >> v >> w; u--; v--;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }
    static bool visited[MAX];
    stack<uint32_t> to_visit;
    to_visit.push(0); visited[0] = true;
    static int32_t jump_val[MAX][MAXLOG];
    static uint32_t jump[MAX][MAXLOG], depth[MAX];
    for(uint32_t u = 0; u < n; u++)
    {
        for(uint32_t p = 0; p < logn; p++)
        {
            jump[u][p] = -1u;
            jump_val[u][p] = -INF_I32;
        }
    }
    while(not to_visit.empty())
    {
        uint32_t u = to_visit.top(); to_visit.pop();
        for(auto e : graph[u])
        {
            uint32_t v; int32_t w;
            tie(v, w) = e;
            if(not visited[v])
            {
                to_visit.push(v); visited[v] = true;
                depth[v] = depth[u] + 1;
                jump[v][0] = u; jump_val[v][0] = w;
                for(uint32_t p = 1; p < logn; p++)
                {
                    uint32_t x = jump[v][p-1];
                    if(x == -1u)
                        break;
                    jump[v][p] = jump[x][p-1];
                    jump_val[v][p] = max(jump_val[v][p-1], jump_val[x][p-1]);
                }
            }
        }
    }
    int32_t a;
    while(true)
    {
        cin >> a;
        if(a == -1)
            break;
        uint32_t u = a, v;
        cin >> v; u--; v--;
        if(u == v)
        {
            cout << "0\n";
            continue;
        }
        int32_t r = -INF_I32;
        if(depth[u] < depth[v])
            swap(u, v);
        for(uint32_t p = logn; p --> 0;)
        {
            if(jump[u][p] != -1u and depth[jump[u][p]] >= depth[v])
                r = max(r, jump_val[u][p]), u = jump[u][p];
        }
        if(u != v)
        {
            for(uint32_t p = logn; p --> 0;)
            {
                if(jump[u][p] != jump[v][p] and jump[u][p] != -1u)
                {
                    r = max(r, max(jump_val[u][p], jump_val[v][p]));
                    u = jump[u][p], v = jump[v][p];
                }
            }
            r = max(r, max(jump_val[u][0], jump_val[v][0]));
        }
        cout << r << "\n";
    }
}
