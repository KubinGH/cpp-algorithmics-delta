#include <bits/stdc++.h>

using namespace std;

struct edge_t
{
    uint32_t u, v; long double w;
    edge_t() {}
    edge_t(uint32_t u, uint32_t v, long double w) : u(u), v(v), w(w) {}
};

int main()
{
    uint32_t n, m;
    cin >> n >> m;
    cout << fixed << setprecision(6);
    vector<edge_t> edges(m);
    long double lo = 0, hi = 0;
    for(uint32_t i = 0; i < m; i++)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].u--; edges[i].v--;
        lo = min(lo, edges[i].w);
        hi = max(hi, edges[i].w);
    }
    vector<long double> dist(n);
    while(hi - lo > 1.0L/(long double)(1<<20))
    {
        long double c = (lo + hi) / 2;
        bool any_last = false;
        fill(dist.begin(), dist.end(), 0.0L);
        for(uint32_t t = 0; t < n; t++)
        {
            for(edge_t e : edges)
            {
                if(dist[e.u] + (e.w - c) < dist[e.v])
                {
                    any_last = t == n - 1;
                    dist[e.v] = dist[e.u] + (e.w - c);
                }
            }
        }
        if(any_last)
            hi = c;
        else
            lo = c;
    }
    cout << (lo+hi)/2;
}
