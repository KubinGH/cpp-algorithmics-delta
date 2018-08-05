#include <utility>
#include <tuple>
#include <cstdio>
#define V first
#define W second
#ifndef _WIN32
#define getchar getchar_unlocked
#endif // _WIN32

using namespace std;

const size_t MAX = 1 << 20;

typedef pair<uint32_t, uint32_t> edge_t;
typedef pair<uint32_t, uint64_t> edge64_t;

void load_uint32(uint32_t* p)
{
    char ch = getchar();
    *p = ch - '0';
    while('0' <= (ch = getchar()) and ch <= '9')
        *p *= 10, *p += ch - '0';
}

int main()
{
    uint32_t n;
    load_uint32(&n);
    static uint32_t edgecount[MAX];
    static struct { uint32_t u, v, w; } edges[MAX];
    for(uint32_t i = 0; i < n - 1; i++)
    {
        auto& e = edges[i];
        load_uint32(&e.u); load_uint32(&e.v); load_uint32(&e.w);
        ++edgecount[--e.u]; ++edgecount[--e.v];
    }
    static edge64_t BLOCK0[2*MAX], BLOCK1[MAX];
    static edge64_t* graph[MAX];
    static uint32_t idx[MAX];
    for(uint32_t i = 0, z = 0; i < n; i++)
        graph[i] = BLOCK0+z, idx[i] = edgecount[i], z += edgecount[i];
    for(uint32_t i = 0; i < n - 1; i++)
    {
        auto& e = edges[i];
        graph[e.u][--idx[e.u]] = {e.v, e.w};
        graph[e.v][--idx[e.v]] = {e.u, e.w};
    }
    static bool vis[MAX]; vis[0] = true;
    static uint32_t tovis[MAX]; uint32_t vi = 1;
    static edge64_t parent[MAX]; parent[0].V = -1u;
    static edge64_t* children[MAX];
    static uint32_t topo[MAX]; uint32_t ti = 0;
    uint32_t y = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t u = tovis[i];
        topo[ti++] = u;
        children[u] = BLOCK1+y;
        for(uint32_t j = 0; j < edgecount[u]; j++)
        {
            auto& e = graph[u][j];
            uint32_t v = e.V, w = e.W;
            if(not vis[v])
            {
                vis[v] = true;
                tovis[vi++] = v;
                parent[v] = {u, w};
                children[u][idx[u]++] = {v, w};
            }
        }
        y += idx[u];
    }
    static uint64_t T[MAX], P[MAX], C[MAX];
    for(uint32_t i = n; i --> 0;)
    {
        uint32_t u = topo[i];
        C[u] = 1;
        for(uint32_t j = 0; j < idx[u]; j++)
        {
            auto& e = children[u][j];
            C[u] += C[e.V];
            T[u] += T[e.V] + C[e.V]*e.W;
        }
    }
    P[0] = T[0];
    uint64_t n64 = n;
    for(uint32_t i = 1; i < n; i++)
    {
        uint32_t u = topo[i];
        P[u] = P[parent[u].V] + n64 * parent[u].W - 2 * C[u] * parent[u].W;
    }
    for(uint32_t i = 0; i < n; i++)
        printf("%llu\n", P[i]);
}
