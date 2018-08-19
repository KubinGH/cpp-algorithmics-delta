#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 17, MAX_SQRT = 362;

typedef tuple<uint32_t, uint32_t, uint32_t> tri_u32;

struct edge_t
{
    uint32_t v, w;
    edge_t() {}
    edge_t(uint32_t v, uint32_t w) : v(v), w(w) {}
    bool operator< (const edge_t& rhs) const
        { return w < rhs.w; }
    bool operator> (const edge_t& rhs) const
        { return w > rhs.w; }
};

struct disjoint_set
{
    uint32_t parent[MAX], nrank[MAX];
    disjoint_set(uint32_t init = MAX)
    {
        iota(parent, parent + init, 0);
    }
    uint32_t find_root(uint32_t node)
    {
        if(parent[node] == node)
            return node;
        return parent[node] = find_root(parent[node]);
    }
    void unite(uint32_t first_node, uint32_t second_node)
    {
        uint32_t first = find_root(first_node), second = find_root(second_node);
        if(nrank[first] < nrank[second])
            parent[first] = second;
        else
        {
            if(nrank[first] == nrank[second])
                nrank[first]++;
            parent[second] = first;
        }
    }
};
struct keeper_disjoint_set
{
    uint32_t parent[MAX], nrank[MAX], ncount[MAX], result[MAX];
    keeper_disjoint_set(uint32_t init = MAX)
    {
        iota(parent, parent + init, 0);
        fill(ncount, ncount + init, 1);
    }
    uint32_t find_root(uint32_t node)
    {
        if(parent[node] == node)
            return node;
        return parent[node] = find_root(parent[node]);
    }
    uint32_t unite(uint32_t first_node, uint32_t second_node)
    {
        uint32_t first = find_root(first_node), second = find_root(second_node);
        if(nrank[first] < nrank[second])
        {
            parent[first] = second;
            result[second] = max(result[first], result[second]);
            ncount[second] += ncount[first];
            return second;
        }
        else
        {
            if(nrank[first] == nrank[second])
                nrank[first]++;
            parent[second] = first;
            result[first] = max(result[first], result[second]);
            ncount[first] += ncount[second];
            return first;
        }
    }
};
keeper_disjoint_set caches[MAX_SQRT];
keeper disjoint_set cdset;
uint32_t cache_idx = -1u;
uint32_t mtime[MAX], ctime = 0;
uint32_t c_update_node(uint32_t node)
{
    if(ctime != mtime[node])
    {
        mtime[node] = ctime;
        cdset.parent[node] = caches[cache_idx].parent[node];
        cdset.nrank[node] = caches[cache_idx].nrank[node];
        cdset.ncount[node] = caches[cache_idx].ncount[node];
        cdset.result[node] = caches[cache_idx].result[node];
    }
}
uint32_t c_find_root(uint32_t node)
{
    c_update_node(node);
    if(parent[node] == node)
        return node;
    return parent[node] = find_root(parent[node]);
}
uint32_t c_unite(uint32_t first_node, uint32_t second_node)
{
    uint32_t first = find_root(first_node), second = find_root(second_node);
    if(nrank[first] < nrank[second])
    {
        parent[first] = second;
        result[second] = max(result[first], result[second]);
        ncount[second] += ncount[first];
        return second;
    }
    else
    {
        if(nrank[first] == nrank[second])
            nrank[first]++;
        parent[second] = first;
        result[first] = max(result[first], result[second]);
        ncount[first] += ncount[second];
        return first;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static vector<edge_t> graph[MAX];
    priority_queue<tri_u32, vector<tri_u32>, greater<tri_u32>> Q;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        Q.emplace(i+1, u, v);
    }
    static disjoint_set dset;
    vector<tri_u32> edges;
    while(not Q.empty())
    {
        tri_u32 t = Q.top(); Q.pop();
        uint32_t w, u, v; tie(w, u, v) = t;
        if(dset.find_root(u) != dset.find_root(v))
        {
            dset.unite(u, v);
            graph[u].emplace_back(v, w);
            graph[v].emplace_back(u, w);
            edges.emplace_back(w, u, v);
        }
    }
    sort(edges.begin(), edges.end());
    uint32_t q;
    cin >> q;
    while(q --> 0)
    {
        uint32_t u, v, z;
        cin >> u >> v >> z; u--; v--;
    }
}
