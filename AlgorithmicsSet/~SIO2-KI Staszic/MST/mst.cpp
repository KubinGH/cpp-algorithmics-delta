#include <bits/stdc++.h>

using namespace std;

typedef tuple<int32_t, uint32_t, uint32_t, uint32_t> edge_t;

const size_t MAX = 1000000;

struct disjoint_set
{
    array<uint32_t, MAX> parent, nrank, ncount;
    disjoint_set()
    {
        iota(parent.begin(), parent.end(), 0);
        nrank[0] = MAX + 1;
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
    uint32_t n, m;
    cin >> n >> m;
    priority_queue<edge_t, vector<edge_t>, greater<edge_t>> Q;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v; int32_t w;
        cin >> u >> v >> w; u--; v--;
        Q.emplace(w, u, v, i);
    }
    static disjoint_set dset;
    while(dset.ncount[0] < n and not Q.empty())
    {
        edge_t e = Q.top(); Q.pop();
        uint32_t u = get<1>(e), v = get<2>(e), i = get<3>(e);
        if(dset.find_root(u) != dset.find_root(v))
        {
            cout << i+1 << '\n';
            dset.unite(u, v);
        }
    }
}
