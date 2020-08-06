#include <bits/stdc++.h>

using namespace std;

struct disjoint_sets
{
    vector<size_t> repr, rank;

    disjoint_sets(size_t n) : repr(n), rank(n)
    {
        iota(repr.begin(), repr.end(), 0);
        iota(rank.begin(), rank.end(), 0);
        shuffle(rank.begin(), rank.end(), mt19937{});
    }

    size_t find(size_t u)
    {
        return u == repr[u] ? u : repr[u] = find(repr[u]);
    }
    bool unite(size_t u, size_t v)
    {
        if((u = find(u)) == (v = find(v)))
            return false;
        if(rank[u] > rank[v])
            swap(u, v);
        repr[v] = u;
        return true;
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<size_t> fst(m, SIZE_MAX), snd(m), deg(n);
    vector<vector<size_t>> graph(n);
    for(size_t u = 0; u < n; u++)
    {
        cin >> deg[u];
        for(size_t j = 0; j < deg[u]; j++)
        {
            size_t i;
            cin >> i; i--;
            (fst[i] == SIZE_MAX ? fst[i] : snd[i]) = u;
        }
    }
    for(size_t i = 0; i < m; i++)
    {
        if(deg[fst[i]] > deg[snd[i]])
            swap(fst[i], snd[i]);
        graph[fst[i]].push_back(snd[i]);
    }

    vector<bool> open(n);
    disjoint_sets desu(n);

    size_t q;
    cin >> q;

    while(q --> 0)
    {
        size_t k;
        cin >> k;

        vector<size_t> lst(k);
        for(auto& u : lst)
            cin >> u, u--, open[u] = true;

        size_t e = 0, c = k;
        for(auto u : lst)
        {
            for(auto v : graph[u])
            {
                if(open[v])
                {
                    e++;
                    c -= desu.unite(u, v);
                }
            }
        }

        for(auto u : lst)
            open[u] = false, desu.repr[u] = u;

        cout << e-k+c << '\n';
    }
}
