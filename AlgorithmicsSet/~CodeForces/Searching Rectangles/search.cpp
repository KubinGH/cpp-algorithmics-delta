// To chyba nie jest heura.

#include <bits/stdc++.h>

using namespace std;

#ifdef XHOVA
uint32_t Ax1, Ay1, Ax2, Ay2, Bx1, By1, Bx2, By2;
#endif

struct point_t
{
    uint32_t x, y;
};

struct rect_t
{
    uint32_t x1, y1, x2, y2;
    bool operator< (const rect_t& o) const
    {
        return tie(x1, y1, x2, y2) < tie(o.x1, o.y1, o.x2, o.y2);
    }
    uint64_t area() const
    {
        return (uint64_t) (x2 - x1 + 1) * (y2 - y1 + 1);
    }
    bool degenerate() const
    {
        return not (x1 <= x2 and y1 <= y2);
    }
};
rect_t intersect(const rect_t& a, const rect_t& b)
{
    return {max(a.x1, b.x1), max(a.y1, b.y1),
            min(a.x2, b.x2), min(a.y2, b.y2)};
}

struct communications
{
    uint32_t operator() (uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)
    {
        cout << "? " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
        uint32_t b;
#ifdef XHOVA
        b = int(x1 <= Ax1 and Ax2 <= x2 and y1 <= Ay1 and Ay2 <= y2) +
            int(x1 <= Bx1 and Bx2 <= x2 and y1 <= By1 and By2 <= y2);
        cerr << "< " << b << endl;
#else
        cin >> b;
#endif
        return b;
    }
    void answer(uint32_t ax1, uint32_t ay1, uint32_t ax2, uint32_t ay2,
                uint32_t bx1, uint32_t by1, uint32_t bx2, uint32_t by2)
    {
        cout << "! " << ax1 << " " << ay1 << " " << ax2 << " " << ay2 << " "
                     << bx1 << " " << by1 << " " << bx2 << " " << by2 << endl;
    }
    uint32_t operator() (const rect_t& r)
        { return operator() (r.x1, r.y1, r.x2, r.y2); }
    void answer(const rect_t& a, const rect_t& b)
        { return answer(a.x1, a.y1, a.x2, a.y2, b.x1, b.y1, b.x2, b.y2); }
};

template<typename Arg, typename Callable>
uint32_t first_true(Arg lo, Arg hi, Callable func)
{
    while(lo < hi)
    {
        Arg mid = (lo + hi) / 2;
        if(func(mid))
            hi = mid;
        else
            lo = mid+1;
    }
    return lo;
}


int __main()
{
    uint32_t n;
    cin >> n;
#ifdef XHOVA
    cin >> Ax1 >> Ay1 >> Ax2 >> Ay2 >> Bx1 >> By1 >> Bx2 >> By2;
#endif
    communications comm;
    vector<uint32_t> X = {
        first_true(1u, n+1, [&](uint32_t x) { return comm(1, 1, x, n) >= 1; }),
        first_true(1u, n+1, [&](uint32_t x) { return comm(1, 1, x, n) >= 2; }),
        n-first_true(0u, n, [&](uint32_t xt) { return comm(n-xt, 1, n, n) >= 1; }),
        n-first_true(0u, n, [&](uint32_t xt) { return comm(n-xt, 1, n, n) >= 2; }),
    };
    vector<uint32_t> Y = {
        first_true(1u, n+1, [&](uint32_t y) { return comm(1, 1, n, y) >= 1; }),
        first_true(1u, n+1, [&](uint32_t y) { return comm(1, 1, n, y) >= 2; }),
        n-first_true(0u, n, [&](uint32_t yt) { return comm(1, n-yt, n, n) >= 1; }),
        n-first_true(0u, n, [&](uint32_t yt) { return comm(1, n-yt, n, n) >= 2; }),
    };
    sort(X.begin(), X.end()); sort(Y.begin(), Y.end());
    set<pair<rect_t, rect_t>> candidates;
    for(uint32_t axi = 0; axi < 4; axi++)
      for(uint32_t axj = axi+1; axj < 4; axj++)
        for(uint32_t ayi = 0; ayi < 4; ayi++)
          for(uint32_t  ayj = ayi+1; ayj < 4; ayj++)
    {
        uint32_t bxi = -1u, bxj = 0, byi = -1u, byj = 0;
        for(uint32_t i = 0; i < 4; i++)
        {
            if(axi!=i and axj!=i)
                bxi = min(i, bxi), bxj = max(i, bxj);
            if(ayi!=i and ayj!=i)
                byi = min(i, byi), byj = max(i, byj);
        }
        candidates.emplace(make_pair(
            rect_t{X[axi], Y[ayi], X[axj], Y[ayj]},
            rect_t{X[bxi], Y[byi], X[bxj], Y[byj]}
        ));
    }
    pair<rect_t, rect_t> result = {{1, 1, n, n}, {1, 1, n, n}};
    for(auto p : candidates)
    {
        auto a = p.first, b = p.second;
        if(intersect(a, b).degenerate() and comm(a) == 1 and comm(b) == 1)
        {
            if(a.area() + b.area() < result.first.area() + result.second.area())
                result = {a, b};
        }
    }
    comm.answer(result.first, result.second);
}

int main()
{
    cout << "Zrobione";
    return 0;
    return __main();
}
