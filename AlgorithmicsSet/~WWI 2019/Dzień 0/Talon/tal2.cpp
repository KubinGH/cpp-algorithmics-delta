#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

const int FIX = 1e9;
const size_t NAX = (1u << 31) - 1;

struct point
{
    int x, y;
};

constexpr size_t lsb(size_t x) { return x & -x; }

struct fenwick_tree
{
    __gnu_pbds::gp_hash_table<size_t, int> F;
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
        while(p <= NAX)
            F[p] = max(F[p], v), p += lsb(p);
    }
};

struct fenwick_tree_2d
{
    __gnu_pbds::gp_hash_table<size_t, fenwick_tree> F;
    int get_prefix(size_t x, size_t y)
    {
        int r = 0;
        while(y)
            r = max(r, F[y].get_prefix(x)), y -= lsb(y);
        return r;
    }
    void set(size_t x, size_t y, int v)
    {
        y++;
        while(y <= NAX)
            F[y].set(x, v), y += lsb(y);
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
        points[i] = {x + FIX, y + FIX};
    }

    sort(points.begin(), points.end(), [&](point a, point b) {
        return make_pair(a.x, a.y) < make_pair(b.x, b.y);
    });

    fenwick_tree F;
    size_t mim = points[0].x;

    for(auto p : points)
    {
        cout << p.x-FIX << " " << p.y-FIX << " " << p.x - mim << ": " << F.get_prefix(p.y + (p.x - mim)) + 1 << endl;
        for(int i = -20; i < 20; i++)
            cout << F.get_prefix(FIX+i) << " ";
        cout << endl;
        F.set(p.y, F.get_prefix(p.y + (p.x - mim)) + 1);
    }

    cout << F.get_prefix(NAX);
}

/*
7
-1 0
-4 1
-3 2
-2 -1
1 -1
2 -2
4 -2
*/
