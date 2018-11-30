#include <bits/stdc++.h>

using namespace std;

namespace geometry
{
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

    // Graham scan
    vector<vec2d> find_convex_hull(vector<vec2d> points)
    {
        auto it = min_element(points.begin(), points.end(), [](vec2d a, vec2d b) {
            return make_pair(a.x, a.y) < make_pair(b.x, b.y);
        });
        swap(points.front(), *it);
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
            while(hull.size() > 2 and ori(hull.end()[-2]-s, hull.end()[-1]-s, p-s) < 0)
                hull.pop_back();
            hull.push_back(p);
        }
        hull.pop_back();
        return hull;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<geometry::vec2d> points(n);
    map<pair<uint32_t, uint32_t>, uint32_t> idx;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> points[i].x >> points[i].y;
        idx[{points[i].x, points[i].y}] = i;
    }
    auto hull = geometry::find_convex_hull(points);
    hull.insert(hull.begin(), hull.back());
    hull.insert(hull.end(), hull[1]);
    vector<uint32_t> result;
    for(uint32_t i = 1; i+1 < hull.size(); i++)
        if((hull[i-1] - hull[i]) * (hull[i+1] - hull[i]) >= 0)
            result.push_back(idx[{hull[i].x, hull[i].y}]);
    sort(result.begin(), result.end());
    cout << result.size() << "\n";
    for(auto i : result)
        cout << i+1 << "\n";
}
