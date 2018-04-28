#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;

typedef unsigned int uint32_t;
typedef int int32_t;

struct disjoint_set
{
    uint32_t parent[MAX], nrank[MAX];
    int32_t diff_to_parent[MAX];
    disjoint_set(uint32_t n)
    {
        for(uint32_t i = 0; i < n; i++)
            parent[i] = i;
    }
    uint32_t find_root(uint32_t node)
    {
        if(parent[node] == node)
            return node;
        uint32_t before = parent[node];
        parent[node] = find_root(parent[node]);
        diff_to_parent[node] += diff_to_parent[before];
        return parent[node];
    }
    void unite(uint32_t init1, uint32_t init2, int32_t diff)
    {
        uint32_t node1 = find_root(init1), node2 = find_root(init2);
        if(nrank[node2] > nrank[node1])
            swap(node1, node2), swap(init1, init2), diff = -diff;
        if(nrank[node1] == nrank[node2])
            nrank[node1]++;
        parent[node2] = node1;
        diff_to_parent[node2] += diff + diff_to_parent[init1] - diff_to_parent[init2];
    }
};

int main()
{
    uint32_t n, z;
    scanf("%u %u", &n, &z);
    static disjoint_set dset(n);
    for(uint32_t zi = 0; zi < z; zi++)
    {
        uint32_t i, j; int32_t w;
        scanf("%u %u %d", &i, &j, &w); i--; j--;
        uint32_t ri = dset.find_root(i), rj = dset.find_root(j);
        bool ok = false;
        if(ri != rj)
        {
            dset.unite(i, j, w);
            ok = true;
        }
        else if(dset.diff_to_parent[j] - dset.diff_to_parent[i] == w)
            ok = true;
        if(ok)
        {
            printf("TAK\n");
        }
        else
        {
            printf("NIE\n");
        }
    }
}
