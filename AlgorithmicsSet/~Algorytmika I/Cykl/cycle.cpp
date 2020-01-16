#include <bits/stdc++.h>

using namespace std;

bool has_negative_cycle(size_t n, const vector<tuple<size_t, size_t, double>>& edges, double malus)
{
    vector<double> D(n);

    for(size_t i = 0; i < n; i++)
    {
        bool a = false;
        for(auto [u, v, d] : edges)
        {
            if(D[u] + d - malus < D[v])
                D[v] = D[u] + d - malus, a = true;
        }
        if(i == n - 1 and a)
            return true;
    }

    return false;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<tuple<size_t, size_t, double>> E(m);
    for(auto& [u, v, d] : E)
        cin >> u >> v >> d, u--, v--, d = -d;

    double lo = -1e5-0xD, hi = 1e5+0xD;

    while(hi - lo > 1e-5)
    {
        auto mid = (lo + hi) / 2;
        if(has_negative_cycle(n, E, mid))
            hi = mid;
        else
            lo = mid;
    }

    cout << fixed << setprecision(4) << -lo;

}
