#include <bits/stdc++.h>

using namespace std;

const int FIX = 1e9;

struct point
{
    int x, y;
};

constexpr size_t lsb(size_t x) { return x & -x; }

struct fenwick_tree
{
    size_t n;
    vector<int> F;
    fenwick_tree(size_t _n) : n(_n), F(n+1) {}
    int get_prefix(size_t p)
    {
        int r = 0;
        while(p)
            r = max(r, F[p]), p -= lsb(p);
        return r;
    }
    void set(size_t p, int v)
    {
        p++;
        while(p <= n)
            F[p] = max(F[p], v), p += lsb(p);
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    size_t n;
    cin >> n;

    vector<point> points(n);
    for(size_t i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        points[i] = {x + FIX, FIX - y};
    }

    sort(points.begin(), points.end(), [&](point a, point b) {
        return make_pair(a.x - a.y, a.x) < make_pair(b.x - b.y, b.x);
    });

    vector<pair<int, size_t>> scale;

    for(size_t i = 0; i < n; i++)
        scale.emplace_back(points[i].y, i);
    sort(scale.begin(), scale.end());
    for(size_t i = 0, f = 0; i < n; i++)
    {
        if(i and scale[i].first != scale[i-1].first)
            f++;
        points[scale[i].second].y = f;
    }

    fenwick_tree F(n);

    for(auto p : points)
        F.set(p.y, F.get_prefix(p.y + 1) + 1);

    cout << F.get_prefix(n);
}
