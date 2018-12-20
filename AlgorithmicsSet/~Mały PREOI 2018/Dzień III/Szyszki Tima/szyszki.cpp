#include <bits/stdc++.h>

using namespace std;

struct disjoint_set
{
    uint32_t n;
    vector<uint32_t> parent, nrank;
    disjoint_set(uint32_t _n) : n(_n)
    {
        parent.resize(n); nrank.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }
    void unite(uint32_t u, uint32_t v)
    {
        if(nrank[v = find(v)] > nrank[u = find(u)])
            swap(u, v);
        parent[v] = u;
        if(nrank[u] == nrank[v])
            nrank[u]++;
    }
    uint32_t find(uint32_t u)
    {
        return parent[u] == u ? u : parent[u] = find(parent[u]);
    }
};


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<uint32_t> A(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    sort(A.begin(), A.end());
    A.erase(unique(A.begin(), A.end()), A.end());
    n = A.size();
    uint32_t M = A.back() + 1;
    vector<uint32_t> L(M, -1u);
    for(uint32_t a = M, i = n; a --> 0; )
    {
        if(i and A[i-1] == a)
            L[a] = i-1, i--;
        else
            L[a] = L[a+1];
    }
    vector<vector<pair<uint32_t, uint32_t>>> E(M);
    for(uint32_t i = 0; i < n; i++)
    {
        for(uint32_t a = A[i]; a < M; a += A[i])
        {
            uint32_t j = L[a];
            if(i == j)
                j++;
            if(j < n)
                E[A[j]%A[i]].emplace_back(i, j);
        }
    }
    disjoint_set dset(n);
    uint32_t r = 0;
    for(uint32_t x = 0; x < M; x++)
        for(auto p : E[x])
            if(dset.find(p.first) != dset.find(p.second))
                r += x, dset.unite(p.first, p.second);
    cout << r;
}
