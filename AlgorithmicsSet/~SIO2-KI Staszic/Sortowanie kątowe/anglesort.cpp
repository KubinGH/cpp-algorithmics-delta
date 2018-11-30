#include <bits/stdc++.h>

using namespace std;

namespace geometry
{
    struct vec2d { int64_t x, y; };
    vec2d operator+ (vec2d a, vec2d b) { return {a.x+b.x, a.y+b.y}; }
    vec2d operator- (vec2d a) { return {-a.x, -a.y}; }
    vec2d operator- (vec2d a, vec2d b) { return a + (-b); }
    int64_t operator* (vec2d a, vec2d b) { return a.x*b.y + a.y*b.x; }
    int64_t operator^ (vec2d a, vec2d b) { return a.x*b.y - a.y*b.x; }
    int64_t operator+ (vec2d a) { return a.x*a.x + a.y*a.y; }
    istream& operator>> (istream& in, vec2d& a) { return in >> a.x >> a.y; }
}

using geometry::vec2d;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    uint32_t n;
    cin >> n;
    vector<vec2d> points(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> points[i];
    auto it = min_element(points.begin(), points.end(), [](vec2d a, vec2d b) {
        return make_pair(a.x, a.y) < make_pair(b.x, b.y);
    });
    swap(*points.begin(), *it);
    auto p = points.front();
    sort(points.begin()+1, points.end(), [p](vec2d a, vec2d b) {
        auto v = (a - p) ^ (b - p);
        if(v == 0)
            return +(a - p) < +(b - p);
        else
            return v > 0;
    });
    for(uint32_t i = 0; i < n; i++)
        cout << points[i].x << " " << points[i].y << "\n";
}
