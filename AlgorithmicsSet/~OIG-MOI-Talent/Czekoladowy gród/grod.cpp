#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;
struct dt { uint32_t i, c; }; // index, count

const size_t MAX = 1000000, JUMP_POINTERS = 21;

static uint32_t jump[MAX][JUMP_POINTERS], depth[MAX];
uint32_t lca(uint32_t u, uint32_t v)
{
    if(depth[u] < depth[v])
        swap(u, v);
    for(uint32_t i = JUMP_POINTERS; i --> 0;)
        if(jump[u][i] != -1u and depth[jump[u][i]] >= depth[v])
            u = jump[u][i];
    if(u == v)
        return u;
    for(uint32_t i = JUMP_POINTERS; i --> 0;)
    {
        if(jump[u][i] != jump[v][i] and jump[u][i] != -1u)
            u = jump[u][i], v = jump[v][i];
    }
    return jump[u][0];
}

uint64_t pairs(uint64_t n)
{
    return (n * (n - 1)) / 2;
}

int main()
{
    uint32_t n;
    scanf("%u", &n);
    static vector<uint32_t> graph[MAX];
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        scanf("%u %u", &u, &v); u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    static bool visited[MAX];
    static uint32_t parent[MAX], topological[MAX]; uint32_t ti = 0;
    static vector<uint32_t> children[MAX];
    queue<uint32_t> to_visit;
    for(uint32_t i = 0; i < n; i++)
        fill(jump[i], jump[i] + JUMP_POINTERS, -1u);
    to_visit.push(0);
    visited[0] = true;
    while(not to_visit.empty())
    {
        uint32_t u;
        u = to_visit.front(); to_visit.pop();
        topological[ti++] = u;
        for(uint32_t i = 0; i < graph[u].size(); i++)
        {
            uint32_t v = graph[u][i];
            if(not visited[v])
            {
                parent[v] = u;
                children[u].push_back(v);
                to_visit.push(v);
                visited[v] = true;
                depth[v] = depth[u] + 1;
                jump[v][0] = u;
                for(uint32_t i = 1; i < JUMP_POINTERS; i++)
                {
                    uint32_t x = jump[v][i-1];
                    if(x == -1u) break;
                    jump[v][i] = jump[x][i-1];
                }
            }
        }
    }
    reverse(topological, topological + n);
    static uint32_t subtree_count[MAX];
    fill(subtree_count, subtree_count + n, 1);
    //static dt subtrees[MAX][2];
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t u = topological[i];
        //subtrees[u][0].i = subtrees[u][1].i = -1u;
        //subtrees[u][0].c = subtrees[u][1].c = 0;
        for(uint32_t j = 0; j < children[u].size(); j++)
        {
            uint32_t v = children[u][j];
            subtree_count[u] += subtree_count[v];
        }
        //cout << u+1 << ": " << subtree_count[u] << " <" << n - subtree_count[u] << ">" << endl;
    }
    uint64_t result = 1llu << 63;
    for(uint32_t u = 0; u < n; u++)
    {
        for(uint32_t v = u+1; v < n; v++)
        {
            uint64_t x = subtree_count[u], y = subtree_count[v];
            uint32_t a = lca(u, v);
            if(a == u)
                x -= y;
            else if(a == v)
                y -= x;
            //cout << u+1 << " & " << v+1 << " -> " << x << " " << y << " " << n - x - y << endl;
            result = min(result, pairs(x) + pairs(y) + pairs(n - x - y));
        }
    }
    cout << result;
}

/*
16
13 7
7 2
2 1
14 8
15 8
8 3
9 3
16 10
10 3
3 1
4 1
11 5
12 5
5 1
6 1
*/
