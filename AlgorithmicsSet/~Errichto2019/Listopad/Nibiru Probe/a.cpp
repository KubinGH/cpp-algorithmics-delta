#include <bits/stdc++.h>

using namespace std;

using num = long double;

struct Point
{
    num x, y;
};

struct Line
{
    num a, b;
    num operator() (num x) const { return a*x + b; }

    num integrate(num x1, num x2)
    {
        return (x2 - x1)*(a/2*(x2 + x1) + b);
    }
};

Line operator- (const Line& p) { return {-p.a, -p.b}; }
Line operator+ (const Line& p, const Line& q) { return {p.a + q.a, p.b + q.b}; }
Line operator- (const Line& p, const Line& q) { return p + (-q); }
Line& operator+= (Line& p, const Line& q) { return p = p + q; }
Line& operator-= (Line& p, const Line& q) { return p = p - q; }

Line interpolate(Point A, Point B)
{
    num a = (B.y - A.y) / (B.x - A.x);
    return {a, A.y - a*A.x};
}

int main()
{
#ifndef XHOVA
    ifstream cin("probe.in");
    ofstream cout("probe.out");
#endif

    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, L;
    cin >> n >> L;

    int minX = INT_MAX, maxX = INT_MIN;
    vector<pair<int, int>> polygon(n);
    for(auto& [x, y] : polygon)
    {
        cin >> x >> y;
        minX = min(x, minX);
        maxX = max(x, maxX);
    }
    polygon.push_back(polygon.front());

    const size_t m = max(size_t(maxX - minX), L) + 0xD;
    vector<Line> diff(m), cover(m);
    vector<num> area_frag(m), area_till(m+1);

    for(size_t i = 0; i < n; i++)
    {
        auto [x1, y1] = polygon[i];
        auto [x2, y2] = polygon[i+1];
        if(x1 == x2) continue;

        x1 -= minX; x2 -= minX;

        auto seg = interpolate({(num)x1, (num)y1}, {(num)x2, (num)y2});
        if(x1 > x2)
            swap(x1, x2), swap(y1, y2);
        else
            seg = -seg;
        diff[x1] += seg;
        diff[x2] -= seg;
    }

    partial_sum(diff.begin(), diff.end(), cover.begin());

    for(size_t x = 0; x < m; x++)
        area_frag[x] = cover[x].integrate(x, x+1);
    partial_sum(area_frag.begin(), area_frag.end(), area_till.begin() + 1);

    auto area = [&](size_t x1, size_t x2) {
        return area_till[x2] - area_till[x1];
    };

    num result = 0;
    for(size_t x = 0; x+L < m; x++)
    {
        num base = area(x+1, x+L);

        result = max(result, area(x, x+L));
        auto f = [&](num e) {
            return cover[x].integrate(x+e, x+1) + base + cover[x+L].integrate(x+L, x+L+e);
        };
        num a = 0, b = 1;
        while(b - a > 1e-10)
        {
            num c = a + (b-a)/3, d = b - (b-a)/3;
            if(f(c) < f(d))
                a = c;
            else
                b = d;
        }
        result = max(result, f(a));
    }

    cout << fixed << setprecision(6) << result;
}
