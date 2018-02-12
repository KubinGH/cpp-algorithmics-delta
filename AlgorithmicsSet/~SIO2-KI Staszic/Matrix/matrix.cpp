#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500002, MAX_E = 1000002;
array<bool, MAX> IG;

struct dt
{
    uint32_t a, b, t;
};
bool operator< (const dt& lhs, const dt& rhs)
{
    return lhs.t > rhs.t;
}

struct disjoint_set
{
    array<uint32_t, MAX> parent, gcount;
    array<uint64_t, MAX> nrank;
    uint32_t max_gcount = 1;
    disjoint_set(uint32_t init = MAX)
    {
        for(uint32_t i = 0; i < init+1; i++)
            parent[i] = i;
    }
    uint32_t find_root(uint32_t node)
    {
        if(node == parent[node])
            return node;
        parent[node] = find_root(parent[node]);
        return parent[node];
    }
    void unite(uint32_t nfirst, uint32_t nsecond)
    {
        uint32_t first = find_root(nfirst), second = find_root(nsecond);
        if(first == second) return;
        if(nrank[second] > nrank[first])
        {
            nrank[second]++;
            parent[first] = second;
            gcount[second] += gcount[first];
            max_gcount = max(max_gcount, gcount[second]);
        }
        else
        {
            nrank[first]++;
            parent[second] = first;
            gcount[first] += gcount[second];
            max_gcount = max(max_gcount, gcount[first]);
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m, k;
    cin >> n >> m >> k;
    if(k == 1)
    {
        cout << "KEEP CALM AND FOLLOW THE WHITE RABBIT";
        return 0;
    }
    if(m == 0 or k > m - 1)
    {
        cout << -1;
        return 0;
    }
    static disjoint_set dset(n);
    static array<uint32_t, MAX> G;
    for(uint32_t i = 0; i < k; i++)
    {
        cin >> G[i];
        IG[G[i]] = true;
        dset.gcount[G[i]] = 1;
        dset.nrank[G[i]] = 1llu << 38;
    }
    static array<dt, MAX_E> E;
    for(uint32_t i = 0; i < m; i++)
        cin >> E[i].a >> E[i].b >> E[i].t;
    sort(E.begin(), E.begin() + m);
    uint32_t mi;
    bool ok = false;
    for(mi = 0; mi < m; mi++)
    {
        dset.unite(E[mi].a, E[mi].b);
        if(dset.max_gcount == k)
        {
            ok = true;
            break;
        }
    }
    if(ok)
        cout << E[mi].t - 1;
    else
        cout << -1;
}
