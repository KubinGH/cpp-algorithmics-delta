#include <bits/stdc++.h>

using namespace std;

struct disjoint_sets
{
    vector<size_t> repr, size;

    disjoint_sets(size_t n) : repr(n), size(n, 1)
    {
        iota(repr.begin(), repr.end(), 0);
    }

    size_t find(size_t u)
    {
        return u == repr[u] ? u : repr[u] = find(repr[u]);
    }

    bool unite(size_t u, size_t v)
    {
        if((u = find(u)) == (v = find(v)))
            return false;
        if(size[u] > size[v])
            swap(u, v);
        size[v] += size[u];
        size[u] = 0;
        repr[u] = v;
        return true;
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    disjoint_sets desu(n);
    size_t count = n, maximum = 1;

    while(m --> 0)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        count -= desu.unite(u, v);
        maximum = max(maximum, desu.size[desu.find(u)]);
        cout << count << ' ' << maximum << '\n';
    }
}
