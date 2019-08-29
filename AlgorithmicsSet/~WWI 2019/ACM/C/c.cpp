#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-6;

struct fraction
{
    int n, d;
};

struct edge
{
    size_t u, v;
    fraction w;
    size_t i;
};

template<typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

vector<edge> dijkstra(size_t n, const vector<edge>& edges, double malus, size_t source)
{
    auto cost = [&](fraction w) {
        return double(w.n - w.d*malus);
    };

    vector<vector<edge>> graph(n);
    for(auto e : edges)
        graph[e.u].push_back(e);
    vector<edge> prev(n, {0, 0, {0, 0}, SIZE_MAX});

    vector<double> dist(n, DBL_MAX);
    min_priority_queue<pair<double, size_t>> Q;
    auto maybe = [&](size_t u, double d, edge e) {
        if(d + eps < dist[u])
            Q.emplace(dist[u] = d, u), prev[u] = e;
    };
    maybe(source, 0, {0, 0, {0, 0}, SIZE_MAX});
    while(not Q.empty())
    {
        auto p = Q.top(); Q.pop();
        size_t u = p.second;
        for(auto e : graph[u])
            maybe(e.v, dist[u] + cost(e.w), e);
    }
    return prev;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<edge> edges;
    edges.reserve(2*m);

    for(size_t i = 0; i < m; i++)
    {
        edge e;
        cin >> e.u >> e.v >> e.w.n >> e.w.d;
        e.u--; e.v--;
        e.i = 2*i;
        edges.push_back(e);
        swap(e.u, e.v);
        e.i = 2*i+1;
        edges.push_back(e);
    }

    m *= 2;

    {
        auto prev = dijkstra(n, edges, 0, 0);
        if(prev[1].i == SIZE_MAX)
        {
            cout << "NIE";
            return 0;
        }
    }

    auto recover = [&](double malus) {
        auto cost = [&](fraction w) {
            return double(w.n - w.d*malus);
        };

        auto z_edges = edges;
        vector<size_t> I;
        vector<bool> taken(m);
        for(auto e : edges)
        {
            if(not taken[e.i] and cost(e.w) < eps)
            {
                taken[e.i] = true;
                I.push_back(e.i);
                z_edges[e.i].w = {0, 0};
            }
        }

        auto prev = dijkstra(n, z_edges, malus, 0);
        size_t c = 1;
        do {
            I.push_back(prev[c].i);
            taken[prev[c].i] = true;
            c = prev[c].u;
        } while(c > 0);

        for(auto& i : I)
            i /= 2;
        sort(I.begin(), I.end());
        I.erase(unique(I.begin(), I.end()), I.end());
        for(auto& i : I)
            i *= 2;

        double sum = 0;
        for(auto i : I)
            sum += cost(edges[i].w);

        return make_pair(I, sum);
    };

    double lo = 0, hi = 101;
    while(hi - lo > eps)
    {
        double mid = (lo + hi) / 2;

        auto sum = recover(mid).second;

        if(sum < 0)
            hi = mid;
        else
            lo = mid+eps;
    }

    auto used = recover(lo).first;
    fraction sum = {0, 0};
    for(auto i : used)
        sum.n += edges[i].w.n, sum.d += edges[i].w.d;

    auto g = __gcd(sum.n, sum.d);
    sum.n /= g;
    sum.d /= g;

    cout << sum.n << "/" << sum.d << endl;
}
