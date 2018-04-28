#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;
typedef pair<uint32_t, uint32_t> pair_u32;

const size_t MAX = 1e5;

struct disjoint_set
{
    uint32_t parent[MAX], nrank[MAX], ncount[MAX];
    disjoint_set()
    {
        for(uint32_t i = 0; i < MAX; i++)
            parent[i] = i;
        fill(ncount, ncount + MAX, 1);
    }
    uint32_t find_root(uint32_t node)
    {
        if(parent[node] == node)
            return node;
        parent[node] = find_root(parent[node]);
        return parent[node];
    }
    void unite(uint32_t first, uint32_t second)
    {
        first = find_root(first); second = find_root(second);
        if(first == second) return;
        if(nrank[first] < nrank[second])
            parent[first] = second, ncount[second] += ncount[first];
        else
        {
            parent[second] = first;
            nrank[first] += nrank[first] == nrank[second];
            ncount[first] += ncount[second];
        }
    }

};

uint32_t diff_min0(uint32_t a, uint32_t b)
{
    return a >= b ? a - b : 0;
}
uint32_t max(uint32_t a, uint32_t b)
{
    return a > b ? a : b;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, z, f;
    scanf("%u %u %u", &n, &z, &f);
    static uint32_t A[MAX];
    priority_queue<pair_u32, vector<pair_u32>, greater<pair_u32> > Q;
    static disjoint_set dset;
    uint32_t v = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        scanf("%u", A+i);
        if(i > 0)
        {
            if(A[i-1] < A[i])
                dset.unite(i - 1, i);
            else if((A[i-1]-A[i]+1) <= n*f/z+10)
                Q.push(make_pair(A[i-1] - A[i] + 1, i));
        }
        v = max(v, dset.ncount[dset.find_root(i)]);
    }
    uint32_t k = 0;
    uint32_t r = v * f;
    while(not Q.empty())
    {
        pair_u32 p = Q.top(); Q.pop();
        k = p.first;
        dset.unite(p.second - 1, p.second);
        v = max(v, dset.ncount[dset.find_root(p.second)]);
        r = max(r, diff_min0(v * f, k * z));
    }
    printf("%u", r);
}
