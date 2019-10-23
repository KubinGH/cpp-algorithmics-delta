#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 30;

struct fenwick_tree
{
    unordered_map<size_t, uint> F;

    static constexpr size_t lsb(size_t x) { return x & -x; }

    uint get_prefix(size_t p)
    {
        uint r = 0;
        while(p)
            r += F.count(p) ? F[p] : 0, p -= lsb(p);
        return r;
    }
    void delta(size_t p, uint v)
    {
        while(p < MAX)
            F[p] += v, p += lsb(p);
    }
};

struct fenwick_tree_2d
{
    unordered_map<size_t, fenwick_tree> F;
    static constexpr size_t lsb(size_t x) { return x & -x; }

    uint get_prefix(size_t x, size_t y)
    {
        uint r = 0;
        while(y)
            r += F.count(y) ? F[y].get_prefix(x) : 0, y -= lsb(y);
        return r;
    }
    void delta(size_t x, size_t y, uint v)
    {
        cout << "(" << x << ", " << y << ") += " << v << endl;
        while(y < MAX)
            F[y].delta(x, v), y += lsb(y);
    }
    void deltar(size_t x1, size_t y1, size_t x2, size_t y2, uint v)
    {
        delta(x1, y1, v);
        delta(x2+1, y1, -v);
        delta(x1, y2+1, -v);
        delta(x2+1, y2+1, v);
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t q;
    cin >> q;

    const size_t n = MAX-10;
    fenwick_tree_2d bitxy, bitx, bity, bit1;
    auto update = [&](uint x1, uint y1, uint x2, uint y2, uint c) {
       bitxy.deltar(x1,   y1,   x2, y2, c);
        bitx.deltar(x1,   y1,   x2, y2, -c*(y1 - 1));
        bitx.deltar(x1,   y2+1, x2, n,  c*(y2 - y1 + 1));
        bity.deltar(x1,   y1,   x2, y2, -c*(x1 - 1));
        bity.deltar(x2+1, y1,   n,  y2, c*(x2 - x1 + 1));
        bit1.deltar(x1,   y1,   x2, y2, c);
        bit1.deltar(x2+1, y1,   n,  y2, -c*(y1 - 1)*(x2 - x1 + 1));
        bit1.deltar(x1,   y2+1, x2, n,  -c*(x1 - 1)*(y2 - y1 + 1));
        bit1.deltar(x2+1, y2+1, n,  n,  c*(x2 - x1 + 1)*(y2 - y1 + 1));
    };
    auto queryp = [&](uint x, uint y) {
        auto a = bitxy.get_prefix(x, y), b = bitx.get_prefix(x, y), c = bity.get_prefix(x, y), d = bit1.get_prefix(x, y);
        cout << a << "/" << b << "/" << c << "/" << d << endl;
        return a*x*y + b*x + c*y + d;
    };
    auto query = [&](size_t x1, size_t y1, size_t x2, size_t y2) {
        return queryp(x1-1, y1-1) + queryp(x2, y2) -
               queryp(x2, y1-1) - queryp(x1-1, y2);
    };

    while(q --> 0)
    {
        size_t t, x1, x2, y1, y2;
        cin >> t >> x1 >> x2 >> y1 >> y2;
        x1++; x2++; y1++; y2++;
        if(t == 1)
        {
            uint v;
            cin >> v;
            update(x1, y1, x2, y2, v);
        }
        else if(t == 2)
            cout << query(x1, y1, x2, y2) << '\n';
        cout << queryp(1, 1) << '\n';
    }
}
