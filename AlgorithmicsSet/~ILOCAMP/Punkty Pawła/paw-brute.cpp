#include <bits/stdc++.h>

using namespace std;

struct vec2d { int64_t x, y; };
vec2d operator+ (vec2d a, vec2d b) { return {a.x+b.x, a.y+b.y}; }
vec2d operator- (vec2d a) { return {-a.x, -a.y}; }
vec2d operator- (vec2d a, vec2d b) { return a + (-b); }
int64_t operator* (vec2d a, vec2d b) { return a.x*b.x + a.y*b.y; }
int64_t operator^ (vec2d a, vec2d b) { return a.x*b.y - a.y*b.x; }
int64_t operator+ (vec2d a) { return a.x*a.x + a.y*a.y; }

template<typename T>
int sgn(T x) { return int(x > 0) - int(x < 0); }
int64_t ori(vec2d a, vec2d b, vec2d c)
    { return (c.y-a.y) * (b.x-a.x) - (b.y-a.y) * (c.x-a.x); }

vector<vec2d> find_convex_hull(vector<vec2d> points)
{
    auto min_it = min_element(points.begin(), points.end(), [](vec2d a, vec2d b) {
        return make_pair(a.x, a.y) < make_pair(b.x, b.y);
    });
    iter_swap(points.begin(), min_it);
    auto s = points.front();
    sort(points.begin()+1, points.end(), [s](vec2d a, vec2d b) {
        auto v = (a - s) ^ (b - s);
        return v == 0 ? +(a - s) < +(b - s) : v > 0;
    });
    points.push_back(points[0]);
    vector<vec2d> hull = {points[0], points[1]};
    for(uint32_t i = 2; i < points.size(); i++)
    {
        auto p = points[i];
        while(hull.size() > 2 and ori(hull.end()[-2]-s, hull.end()[-1]-s, p-s) <= 0)
            hull.pop_back();
        hull.push_back(p);
    }
    hull.pop_back();
    return hull;
}

int64_t polygon_area(const vector<vec2d> vertices)
{
    if(vertices.size() < 3) return 0;
    int64_t result = 0; const uint32_t n = vertices.size();
    for(uint32_t i0 = n-1, i = 0, i1 = 1; i < n; i++, i0++, i1++)
    {
        result += vertices[i].x * (vertices[i1].y - vertices[i0].y);
        if(i0 == n-1) i0 = -1; if(i1 == n-1) i1 = -1;
    }
    return result;
}

int main()
{
    uint32_t n, k;
    cin >> n >> k;
    vector<vec2d> P(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> P[i].x >> P[i].y;
    auto H = P; const uint32_t h = H.size();
    k = min(k, h);
    int64_t result = 0;
    if(h < 30) for(uint32_t m = 0; m < (1u << h); m++) if(__builtin_popcount(m) == k)
    {
        vector<vec2d> V;
        for(uint32_t i = 0; i < n; i++) if(m & (1u << i))
        {
            V.push_back(H[i]);
        }
        V = find_convex_hull(V);
        result = max(result, abs(polygon_area(V)));
    }
    cout << setprecision(1) << fixed << (double)result/2;
}
