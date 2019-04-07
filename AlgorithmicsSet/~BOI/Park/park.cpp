#include <bits/stdc++.h>

using namespace std;

struct vec2d { int64_t x, y; };
struct circle { vec2d p; int64_t r; };

istream& operator>> (istream& in, vec2d& p)
{
    return in >> p.x >> p.y;
}
istream& operator>> (istream& in, circle& c)
{
    return in >> c.p >> c.r;
}

double dist(vec2d a, vec2d b)
{
    return hypot(a.x-b.x, a.y-b.y);
}
double dist(circle a, circle b)
{
    return max(dist(a.p, b.p) - double(a.r+b.r), 0.);
}
double dist(circle a, char d, int64_t w, int64_t h)
{
    int64_t r = 0;
    if(d == 'N')
        r = max(h - a.p.y - a.r, 0ll);
    else if(d == 'W')
        r = max(a.p.x - a.r, 0ll);
    else if(d == 'S')
        r = max(a.p.y - a.r, 0ll);
    else if(d == 'E')
        r = max(w - a.p.x - a.r, 0ll);
    return r;
}

struct disjoint_set
{
    size_t n;
    vector<size_t> parent, nrank;
    disjoint_set(size_t _n) : n(_n)
    {
        parent.resize(n); nrank.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }
    void unite(size_t u, size_t v)
    {
        if(nrank[v = find(v)] > nrank[u = find(u)])
            swap(u, v);
        parent[v] = u;
        if(nrank[u] == nrank[v])
            nrank[u]++;
    }
    size_t find(size_t u)
    {
        return parent[u] == u ? u : parent[u] = find(parent[u]);
    }
};

using pair_u32 = pair<uint32_t, uint32_t>;
const map<pair_u32, vector<pair_u32>> connection_blocks = {
    {{0, 1}, {{3, 0}, {3, 1}, {3, 2}}},
    {{0, 2}, {{0, 1}, {0, 2}, {3, 1}, {3, 2}}},
    {{0, 3}, {{2, 0}, {2, 1}, {2, 3}}},
    {{1, 2}, {{0, 1}, {0, 2}, {0, 3}}},
    {{1, 3}, {{0, 2}, {0, 3}, {1, 2}, {1, 3}}},
    {{2, 3}, {{1, 0}, {1, 2}, {1, 3}}}
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m; int64_t w, h;
    cin >> n >> m >> w >> h;
    vector<circle> circles(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> circles[i];

    double max_radius_passage[4][4];
    fill(&max_radius_passage[0][0], &max_radius_passage[4][0], numeric_limits<double>::max());
    const char directions[4] = {'N', 'W', 'S', 'E'};

    vector<tuple<double, uint32_t, uint32_t>> edges;
    for(uint32_t i = 0; i < n; i++)
        for(uint32_t j = i+1; j < n; j++)
            edges.emplace_back(dist(circles[i], circles[j]), i, j);
    for(uint32_t i = 0; i < n; i++)
        for(uint32_t e = 0; e < 4; e++)
            edges.emplace_back(dist(circles[i], directions[e], w, h), i, n+e);
    disjoint_set dset(n+4);
    sort(edges.begin(), edges.end());
    for(uint32_t i = 0; i < edges.size(); i++)
    {
        double d; uint32_t u, v;
        tie(d, u, v) = edges[i];
        dset.unite(u, v);
        uint32_t s[4] = {dset.find(n), dset.find(n+1), dset.find(n+2), dset.find(n+3)};
        for(auto p : connection_blocks)
            if(s[p.first.first] == s[p.first.second])
        {
            for(auto q : p.second)
            {
                double g = max_radius_passage[q.first][q.second];
                if(d < g)
                    max_radius_passage[q.first][q.second] = max_radius_passage[q.second][q.first] = d;
            }
        }
    }

    while(m --> 0)
    {
        double R; uint32_t e;
        cin >> R >> e; e--;

        for(uint32_t f = 0; f < 4; f++)
            if(R*2 <= max_radius_passage[e][f])
                cout << f+1;
        cout << "\n";
    }
}
