#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500000;
const size_t JUMP_POINTER_COUNT = 19;
const uint32_t INF = -1u;

uint32_t lca(uint32_t u, uint32_t v, const array<array<uint32_t, JUMP_POINTER_COUNT>, MAX>& jump_ptrs, const array<uint32_t, MAX>& depth)
{
    if(depth[u] > depth[v])
        swap(u, v);
    for(uint32_t i = JUMP_POINTER_COUNT; i --> 0;)
    {
        if(depth[v] >= (1u << i) and depth[v] - (1u << i) >= depth[u])
            v = jump_ptrs[v][i];
    }
    if(u == v)
        return u;
    for(uint32_t i = JUMP_POINTER_COUNT; i --> 0;)
    {
        if(jump_ptrs[u][i] != jump_ptrs[v][i] and jump_ptrs[u][i] != INF)
        {
            u = jump_ptrs[u][i];
            v = jump_ptrs[v][i];
        }
    }
    return jump_ptrs[u][0];

}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<vector<pair<uint32_t, uint64_t> >, MAX> graph;
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t a, b, c;
        cin >> a >> b >> c; a--; b--;
        graph[a].emplace_back(b, c); graph[b].emplace_back(a, c);
    }
    static array<array<uint32_t, JUMP_POINTER_COUNT>, MAX> jump_ptrs;
    for(uint32_t i = 0; i < n; i++)
        for(uint32_t j = 0; j < JUMP_POINTER_COUNT; j++)
            jump_ptrs[i][j] = INF;
    static array<uint32_t, MAX> depth, parent;
    static array<uint64_t, MAX> root_dist;
    static array<bool, MAX> visited;
    queue<uint32_t> Q;
    Q.push(0);
    visited[0] = true;
    while(not Q.empty())
    {
        uint32_t u = Q.front(); Q.pop();
        for(pair<uint32_t, uint64_t> e : graph[u])
        {
            const uint32_t& v = e.first;
            const uint64_t& w = e.second;
            if(not visited[v])
            {
                visited[v] = true;
                parent[v] = u;
                root_dist[v] = root_dist[u] + w;
                depth[v] = depth[u] + 1;
                jump_ptrs[v][0] = u;
                for(uint32_t i = 1; i < JUMP_POINTER_COUNT; i++)
                    if(jump_ptrs[v][i-1] != INF and jump_ptrs[jump_ptrs[v][i-1]][i-1] != INF)
                        jump_ptrs[v][i] = jump_ptrs[jump_ptrs[v][i-1]][i-1];
                Q.push(v);
            }
        }
    }
    uint32_t u, v;
    while(cin >> u)
    {
        if(u == -1u) break;
        cin >> v; u--; v--;
        cout << root_dist[u] + root_dist[v] - 2*root_dist[lca(u, v, jump_ptrs, depth)] << '\n';
    }
}
