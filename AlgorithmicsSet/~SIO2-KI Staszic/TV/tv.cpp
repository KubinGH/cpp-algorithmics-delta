#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 5000;

typedef pair<uint32_t, uint32_t> pair_u32;
typedef pair<int64_t, int64_t> pair_i64;

uint64_t find_sqrt_ge(uint64_t n)
{
    if(n == 0) return 0;
    else if(n == 1) return 1;
    else if(n == 2) return 2;
    else if(n == 3) return 2;
    else if(n == 4) return 2;
    uint64_t lo = 1, hi = n;
    while(lo < hi)
    {
        uint64_t x = (lo+hi) / 2;
        if(x*x >= n)
            hi = x;
        else
            lo = x + 1;
    }
    return lo;
}

uint64_t dist(pair_i64 a, pair_i64 b)
{
    uint64_t dx = abs(a.first - b.first), dy = abs(a.second - b.second);
    return find_sqrt_ge(dx*dx + dy*dy);
}

struct disjoint_set
{
    array<uint32_t, MAX> parent, nrank, ncount;
    disjoint_set()
    {
        iota(parent.begin(), parent.end(), 0);
        ncount.fill(1);
    }
    uint32_t find_root(uint32_t node)
    {
        if(parent[node] == node)
            return node;
        parent[node] = find_root(parent[node]);
        return parent[node];
    }
    void unite(uint32_t first_node, uint32_t second_node)
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
    priority_queue<pair<uint64_t, pair_u32>,
                   vector<pair<uint64_t, pair_u32> >,
                   greater<pair<uint64_t, pair_u32> > > edge_heap;
    for(uint32_t i = 0; i < n; i++)
    {
        for(uint32_t j = i+1; j < n; j++)
        {
            uint64_t d = dist(points[i], points[j]);
            edge_heap.emplace(d, make_pair(i, j));
        }
    }
    static disjoint_set dset;
    dset.nrank[0] = n + 1;
    uint64_t maxim = edge_heap.top().first;
    while(not edge_heap.empty() and dset.ncount[0] < n)
    {
        pair<uint64_t, pair_u32> e = edge_heap.top(); edge_heap.pop();
        uint64_t w = e.first, u = e.second.first, v = e.second.second;
        if(dset.find_root(u) != dset.find_root(v))
        {
            maxim = max(w, maxim);
            dset.unite(u, v);
        }
    }
    cout << static_cast<uint64_t>(n - 1) * maxim;
}
