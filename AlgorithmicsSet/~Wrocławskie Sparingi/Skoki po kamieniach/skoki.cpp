#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500000;

uint32_t abs_diff(uint32_t a, uint32_t b)
{
    return a > b ? a - b : b - a;
}

template<size_t SIZE>
struct disjoint_set
{
    array<uint32_t, SIZE> parent, nrank, ncount;
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
    void unite(uint32_t node1, uint32_t node2)
    {
        uint32_t root1 = find_root(node1), root2 = find_root(node2);
        if(nrank[root2] > nrank[root1])
        {
            parent[root1] = root2;
            ncount[root2] += ncount[root1];
        }
        else
        {
            if(nrank[root1] == nrank[root2])
                nrank[root1]++;
            parent[root2] = root1;
            ncount[root1] += ncount[root2];
        }
    }

};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> indexes, ordering;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> indexes[i];
        indexes[i]--;
        ordering[indexes[i]] = i;
    }
    static array<uint32_t, MAX-1> distances;
    static array<vector<uint32_t>, MAX> indexes_with_distance;
    for(uint32_t i = 0; i < n - 1; i++)
    {
        distances[i] = abs_diff(ordering[i], ordering[i+1]);
        indexes_with_distance[distances[i]].push_back(i);
    }
    static disjoint_set<MAX-1> dset;
    static bitset<MAX-1> open;
    uint32_t maxim = 0;
    for(uint32_t d = 1; d < n; d++)
    {
        for(uint32_t i : indexes_with_distance[d])
        {
            open[i] = true;
            if(i < n - 1 and open[i+1])
                dset.unite(i, i+1);
            if(i > 0 and open[i-1])
                dset.unite(i, i-1);
            maxim = max(maxim, dset.ncount[dset.find_root(i)]);
        }
        cout << maxim << "\n";
    }
}
