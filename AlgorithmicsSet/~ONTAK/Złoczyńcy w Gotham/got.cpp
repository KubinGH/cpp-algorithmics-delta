#include <bits/stdc++.h>

using namespace std;

struct dt { double r; size_t v, n; };
dt operator+ (const dt& a, const dt& b) { return {a.r+b.r, a.v+b.v, a.n+b.n}; }
dt& operator+= (dt& a, const dt& b) { return a = a + b; }
bool operator< (const dt& a, const dt& b) { return tie(a.r, a.v, a.n) < tie(b.r, b.v, b.n); }

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n;
    cin >> n;

    string aff;
    cin >> aff;

    vector<vector<size_t>> graph(n);
    for(size_t i = 1; i < n; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<size_t> parent(n), order;
    order.reserve(n);
    function<void(size_t, size_t)> root = [&](size_t u, size_t lock) {
        for(auto v : graph[u])
            if(v != lock)
                root(v, parent[v] = u);
        order.emplace_back(u);
    };
    root(0, -1);

    const double eps = 1e-7;
    double lo = 0, hi = 1 + eps;
    while(lo + eps < hi)
    {
        double mid = (lo + hi) / 2;

        vector<array<double, 2>> G(n);
        for(auto u : order)
        {
            if(aff[u] == 'C')
            {
                G[u][0] = -mid;
                for(auto v : graph[u]) if(v != parent[u])
                    G[u][0] += min(G[v][0], G[v][1]);
            }
            else if(aff[u] == 'V')
                G[u][0] = DBL_MAX;
            G[u][1] = 1 - mid;
            for(auto v : graph[u]) if(v != parent[u])
                G[u][1] += min(G[v][0], G[v][1] - 1 + mid);
        }
        auto g = min(G[0][0], G[0][1]);
        if(g < 0)
            hi = mid;
        else
            lo = mid + eps;
    }
    cerr << fixed << setprecision(5) << "lo = " << lo << endl;
    vector<array<dt, 2>> G(n);
    for(auto u : order)
    {
        if(aff[u] == 'C')
        {
            G[u][0] = {-lo, 0, 1};
            for(auto v : graph[u]) if(v != parent[u])
                G[u][0] += min(G[v][0], G[v][1]);
        }
        else if(aff[u] == 'V')
            G[u][0].r = DBL_MAX;
        G[u][1] = {1 - lo, 1, 1};
        for(auto v : graph[u]) if(v != parent[u])
        {
            auto c = G[v][1]; c.r += -1 + lo;
            if(G[v][0] < c)
                G[u][1] += G[v][0];
            else
                G[u][1] += c, G[u][1].v--, G[u][1].n--;
        }
    }

    size_t v1, n1;
    if(G[0][0].r < G[0][1].r)
        v1 = G[0][0].v, n1 = G[0][0].n;
    else
        v1 = G[0][1].v, n1 = G[0][1].n;
    auto d = __gcd(v1, n1);
    v1 /= d; n1 /= d;
    cout << v1 << " " << n1;

}
