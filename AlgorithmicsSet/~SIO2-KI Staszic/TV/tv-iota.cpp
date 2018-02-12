#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 5000;

typedef pair<uint32_t, uint32_t> pair_u32;
typedef pair<int64_t, int64_t> pair_i64;

uint64_t dist(pair_i64 a, pair_i64 b)
{
    uint64_t dx = a.first - b.first, dy = a.second - b.second;
    return ceil(sqrt(dx*dx + dy*dy));
}

struct disjoint_set
{
    array<uint32_t, MAX> parent, nrank, ncount;
    disjoint_set()
    {
        iota(parent.begin(), parent.end(), 0);
        ncount.fill(1);
    }
    uint32_t find_root(const uint32_t node)
    {
        if(parent[node] == node)
            return node;
        else if(parent[parent[node]] == parent[node])
            return parent[node];
        parent[node] = find_root(parent[node]);
        return parent[node];
    }
    void unite(const uint32_t first_node, const uint32_t second_node)
    {
        uint32_t first = find_root(first_node), second = find_root(second_node);
        if(nrank[second] > nrank[first])
        {
            parent[first] = second;
            ncount[second] += ncount[first];
        }
        else
        {
            if(nrank[first] == nrank[second])
                nrank[first]++;
            parent[second] = first;
            ncount[first] += ncount[second];
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<pair_i64, MAX> points;
    for(uint32_t i = 0; i < n; i++)
        cin >> points[i].first >> points[i].second;
    set<pair<uint64_t, pair_u32> > edge_heap;
    static array<bitset<MAX>, MAX> used_edge;
    static disjoint_set dset;
    dset.nrank[0] = n + 1;
    uint64_t maxim = 0;
    while(dset.ncount[0] < n)
    {
        for(uint32_t i = 0; i < n; i++)
        {
            for(uint32_t j = i+1; j < n; j++)
            {
                if(used_edge[i][j] or dset.find_root(i) == dset.find_root(j))
                    continue;
                edge_heap.emplace(dist(points[i], points[j]), make_pair(i, j));
                if(edge_heap.size() >= (1 << 16))
                    edge_heap.erase(prev(edge_heap.end()));
            }
        }
        for(pair<uint64_t, pair_u32> e : edge_heap)
        {
            if(dset.ncount[0] >= n) break;
            uint64_t w = e.first, u = e.second.first, v = e.second.second;
            if(dset.find_root(u) != dset.find_root(v))
            {
                if(w > maxim)
                    maxim = w;
                dset.unite(u, v);
            }
            used_edge[u][v] = true;
        }
        edge_heap.clear();
    }
    cout << static_cast<uint64_t>(n - 1) * maxim;
}
