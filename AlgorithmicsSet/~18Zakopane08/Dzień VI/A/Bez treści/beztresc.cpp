#include <bits/stdc++.h>
#define varl(x) { cerr << #x << " = " << (x) << endl; }

using namespace std;

const size_t MAX = 1 << 17;

typedef pair<uint32_t, uint32_t> pair_u32;
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
        fill(nrank, nrank + n, 0);
        fill(ncount, ncount + n, 1);
        fill(result, result + n, 0);
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
    priority_queue<tri_u32, vector<tri_u32>, greater<tri_u32>> Q;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        Q.emplace(i+1, u, v);
    }
    static disjoint_set prim_dset(n);
    vector<tri_u32> edges;
    while(not Q.empty())
    {
        tri_u32 t = Q.top(); Q.pop();
        uint32_t w, u, v; tie(w, u, v) = t;
        if(prim_dset.find_root(u) != prim_dset.find_root(v))
        {
            prim_dset.unite(u, v);
            graph[u].emplace_back(v, w);
            graph[v].emplace_back(u, w);
            edges.emplace_back(w, u, v);
        }
    }
    sort(edges.begin(), edges.end());
    uint32_t q;
    cin >> q;
    static tri_u32 queries[MAX];
    static pair_u32 bounds[MAX];
    static uint32_t result[MAX];
    for(uint32_t i = 0; i < q; i++)
    {
        uint32_t u, v, z;
        cin >> u >> v >> z; u--; v--;
        queries[i] = tri_u32{u, v, z};
        bounds[i] = {0, n - 1};
        result[i] = -1u;
    }
    while(true)
    {
        static vector<uint32_t> triggers[MAX];
        uint32_t done = 0;
        for(uint32_t i = 0; i < n; i++)
            triggers[i].clear();
        for(uint32_t i = 0; i < q; i++)
        {
            if(bounds[i].first == bounds[i].second)
                done++;
            else
                triggers[(bounds[i].first + bounds[i].second) / 2].push_back(i);
        }
        if(done == q)
            break;
        uint32_t i = 0;
        static keeper_disjoint_set dset;
        dset.init(n);
        for(tri_u32 e : edges)
        {
            uint32_t w, u, v; tie(w, u, v) = e;
            uint32_t rt = dset.unite(u, v);
            dset.result[rt] = max(dset.result[rt], w);
            for(uint32_t t : triggers[i])
            {
                uint32_t a, b, z; tie(a, b, z) = queries[t];
                uint32_t c, p;
                uint32_t a_rt, b_rt;
                if((a_rt = dset.find_root(a)) != (b_rt = dset.find_root(b)))
                {
                    p = max(dset.result[a_rt], dset.result[b_rt]);
                    c = dset.ncount[a_rt] + dset.ncount[b_rt];
                }
                else
                {
                    p = dset.result[a_rt];
                    c = dset.ncount[a_rt];
                }
                if(c >= z)
                {
                    result[t] = min(result[t], p);
                    bounds[t].second = (bounds[t].first + bounds[t].second) / 2;
                }
                else
                    bounds[t].first = (bounds[t].first + bounds[t].second) / 2 + 1;
            }
            i++;
        }
    }
    for(uint32_t i = 0; i < q; i++)
        cout << result[i] << "\n";
}
