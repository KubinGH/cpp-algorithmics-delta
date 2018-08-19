#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 17;

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
    keeper_disjoint_set(uint32_t n = MAX)
    {
        init(n);
    }
    void init(uint32_t n = MAX)
    {
        iota(parent, parent + n, 0);
        fill(ncount, ncount + n, 1);
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

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static vector<edge_t> graph[MAX];
    vector<tri_u32> edges;
    priority_queue<tri_u32, vector<tri_u32>, greater<tri_u32>> Q;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        Q.emplace(i+1, u, v);
    }
    static disjoint_set prim_dset;
    while(not Q.empty())
    {
        tri_u32 t = Q.top(); Q.pop();
        uint32_t w, u, v; tie(w, u, v) = t;
        if(prim_dset.find_root(u) != prim_dset.find_root(v))
        {
            //cout << u+1 << " -> " << v+1 << " @ " << w << endl;
            prim_dset.unite(u, v);
            graph[u].emplace_back(v, w);
            graph[v].emplace_back(u, w);
            edges.emplace_back(w, u, v);
        }
    }
    sort(edges.begin(), edges.end());
    static vector<tri_u32> triggers[MAX];
    static uint32_t queries[MAX];
    uint32_t q;
    cin >> q;
    for(uint32_t i = 0; i < q; i++)
    {
        uint32_t u, v, z;
        cin >> u >> v >> z; u--; v--;
        triggers[u].emplace_back(z, v, i);
        triggers[v].emplace_back(z, u, i);
        queries[i] = -1u;
    }
    for(uint32_t i = 0; i < n; i++)
        sort(triggers[i].rbegin(), triggers[i].rend());
    static keeper_disjoint_set dset;
    for(tri_u32 e : edges)
    {
        uint32_t w, u, v; tie(w, u, v) = e;
        uint32_t rt = dset.unite(u, v);
        dset.result[rt] = max(dset.result[rt], w);
        for(uint32_t pt = 0; pt < 2; pt++)
        {
            while(not triggers[u].empty())
            {
                tri_u32 pt =
                if(dset.ncount[dset.find_root(u)]
                   + dset.ncount[dset.find_root(get<1>(triggers[u].back()))]
                    >= get<0>(triggers[u]))
                {
                    if(queries[get<2>(triggers[u])] != -1u)
                        queries[get<2>(triggers[u])] = min(dset.result[dset.find_root(u)],
                                                           dset.result[dset.find_root(get<1>(triggers[u]))]);
                    triggers[u].pop_back();
                }
            }
            u = v;
        }
    }
    for(uint32_t i = 0; i < q; i++)
        cout << queries[i] << "\n";
}
