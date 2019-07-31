#include <bits/stdc++.h>

// -*- ktl/geometry/vec2d.cpp -*-

#include <cstdint>
#include <tuple>

using std::int64_t;


struct vec2d { int64_t x, y; };
vec2d operator+ (vec2d a, vec2d b) { return {a.x+b.x, a.y+b.y}; }
vec2d operator- (vec2d a) { return {-a.x, -a.y}; }
vec2d operator- (vec2d a, vec2d b) { return a + (-b); }
int64_t operator* (vec2d a, vec2d b) { return a.x*b.x + a.y*b.y; }
int64_t operator^ (vec2d a, vec2d b) { return a.x*b.y - a.y*b.x; }
int64_t operator+ (vec2d a) { return a.x*a.x + a.y*a.y; }

template<typename T>
int sgn(T x) { return int(x > 0) - int(x < 0); }
int64_t ori(vec2d a, vec2d b, vec2d c) { return (b - a) ^ (c - a); }
int64_t area(vec2d a, vec2d b, vec2d c) { return (b - a) ^ (c - b); }

// -$- ktl/geometry/vec2d.cpp -$-


// -*- ktl/geometry/convex_hull.cpp -*-

#include <algorithm>
#include <utility>
#include <vector>

using std::min_element; using std::swap; using std::sort;
using std::vector; using std::make_pair;

template<typename Iterator>
vector<vec2d> find_convex_hull(Iterator first, Iterator last, const bool with_colinear = false)
{
    vector<vec2d> points(first, last);
    auto it = min_element(points.begin(), points.end(), [](vec2d a, vec2d b) {
        return make_pair(a.x, a.y) < make_pair(b.x, b.y);
    });
    swap(points.front(), *it);
    auto s = points.front();
    for(auto& p: points) p = p - s;
    sort(points.begin()+1, points.end(), [s](vec2d a, vec2d b) {
        auto v = a ^ b;
        return v == 0 ? +a > +b : v > 0;
    });
    points.push_back(points[0]);
    vector<vec2d> hull = {points[0], points[1]};
    auto ori_ok = [&](int64_t x) {
        return with_colinear ? x >= 0 : x > 0;
    };
    for(uint32_t i = 2; i < points.size(); i++)
    {
        auto p = points[i];
        while(hull.size() > 2 and not ori_ok(ori(hull.end()[-2], hull.end()[-1], p)))
            hull.pop_back();
        hull.push_back(p);
    }
    hull.pop_back();
    for(auto& p : hull) p = p + s;
    return hull;
}

// -$- ktl/geometry/convex_hull.cpp -$-


using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n;
    cin >> n;

    vector<vec2d> points(n);

    for(size_t i = 0; i < n; i++)
        cin >> points[i].x >> points[i].y;

    auto cmp = [](const vec2d& a, const vec2d& b) {
        return tie(a.x, a.y) < tie(b.x, b.y);
    };

    int result = 0;
    while(not points.empty())
    {
        auto hull = find_convex_hull(points.begin(), points.end(), true);

        sort(points.begin(), points.end(), cmp);
        sort(hull.begin(), hull.end(), cmp);
        vector<vec2d> next(points.size() - hull.size());
        set_difference(points.begin(), points.end(), hull.begin(), hull.end(), next.begin(), cmp);
        points.swap(next);
        result++;
    }

    cout << result;
}
