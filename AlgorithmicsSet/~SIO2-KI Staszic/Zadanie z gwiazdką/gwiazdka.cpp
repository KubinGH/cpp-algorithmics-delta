#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;
const size_t JUMP_POINTER_COUNT = 16;
const uint32_t INF = -1u;

int main()
{
    uint32_t n;
    cin >> n;
    static array<vector<uint32_t>, MAX> graph;
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t a, b;
        cin >> a >> b; a--; b--;
        graph[a].push_back(b); graph[b].push_back(a);
    }
    static array<uint32_t, MAX> parent, depth;
    static array<array<uint32_t, JUMP_POINTER_COUNT>, MAX> jump_ptrs;
    for(uint32_t i = 0; i < n; i++)
        jump_ptrs.fill(INF);
    static bitset<MAX> visited;
    queue<uint32_t> Q;
    Q.push(0);
    while(not Q.empty())
    {
        uint32_t u = Q.front(); Q.pop();
        for(uint32_t v : graph)
        {
            if(not visited[v])
            {
                visited[v] = true;
                depth[v] = depth[u] + 1;
                parent[v] = u;
                jump_ptrs[v][0] = u;
                for(uint32_t i = 1; i < JUMP_POINTER_COUNT and (1 << i) <= depth[u]; i++)
                {
                    if(jump_ptrs[v][i-1] != INF and jump_ptrs[jump_ptrs[v][i-1]] != INF)
                        jump_ptrs[v][i] = jump_ptrs[jump_ptrs[v][i-1]];
                    else
                        break;
                }
            }
        }
    }
    uint32_t q;
    cin >> q;
    for(uint32_t qi = 0; qi < q; qi++)
    {
        uint32_t u, v, a;
        cin >> u >> v >> a; u--; v--; a--;
        if(depth[u] > depth[v])
            swap(u, v);
        for(uint32_t i = JUMP_POINTER_COUNT; i --> 0)
        {
            if(depth[v] >= (1 << i) and depth[v] - (1 << i) >= depth[u])
                v = jump_ptrs[v][i];
        }
    }

}
