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

    vector<tuple<int, size_t, size_t>> edges(m);
    for(auto& [w, u, v] : edges)
        cin >> u >> v >> w, u--, v--;

    sort(edges.begin(), edges.end());
    disjoint_sets desu(n);
    int64_t result = 0;
    size_t cnt = 0;

    for(auto [w, u, v] : edges)
        if(desu.unite(u, v))
            result += w, cnt++;

    if(cnt == n - 1)
        cout << result << endl;
    else
        cout << "IMPOSSIBLE" << endl;
}
