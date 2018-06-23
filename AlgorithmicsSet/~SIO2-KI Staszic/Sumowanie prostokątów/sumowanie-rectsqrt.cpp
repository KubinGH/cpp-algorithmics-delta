#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000014129, MAX_SQRT = 31623;

struct rect_t
{
    uint32_t x1, y1, x2, y2;
    rect_t() : x1(0), y1(0), x2(0), y2(0) {}
    rect_t(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) :
        x1(x1), y1(y1), x2(x2), y2(y2) {}
    bool is_degenerate() const
    {
        return x1 > x2 or y1 > y2;
    }
    rect_t intersect(const rect_t& o) const
    {
        return rect_t(max(x1, o.x1), max(y1, o.y1),
                      min(x2, o.x2), min(y2, o.y2));
    }
    uint32_t area()
    {
        if(is_degenerate()) return 0;
        else return (x2 - x1 + 1) * (y2 - y1 + 1);
    }
    bool operator< (const rect_t& o) const
    {
        return tie(x1, y1, x2, y2) < tie(o.x1, o.y1, o.x2, o.y2);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t q;
    cin >> q;
    vector<pair<rect_t, uint32_t>> rects;
    for(uint32_t i = 0; i < q; i++)
    {
        uint32_t p, a, b, c, d, v;
        cin >> p >> a >> b >> c >> d;
        rect_t r(a, c, b, d);
        if(p == 1)
        {
            cin >> v;
            rects.emplace_back(r, v);
        }
        else if(p == 2)
        {
            uint32_t s = 0;
            for(auto o : rects)
                s += r.intersect(o.first).area() * o.second;
            cout << s << "\n";
        }
    }
}
