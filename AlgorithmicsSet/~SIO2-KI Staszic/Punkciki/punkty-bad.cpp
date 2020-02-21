#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct vec2d { int32_t x, y; };
vec2d operator+ (vec2d a, vec2d b) { return {a.x+b.x, a.y+b.y}; }
vec2d operator- (vec2d a) { return {-a.x, -a.y}; }
vec2d operator- (vec2d a, vec2d b) { return a + (-b); }
int64_t operator* (vec2d a, vec2d b) { return (int64_t)a.x*b.x + (int64_t)a.y*b.y; }
int64_t operator^ (vec2d a, vec2d b) { return (int64_t)a.x*b.y - (int64_t)a.y*b.x; }
int64_t operator+ (vec2d a) { return (int64_t)a.x*a.x + (int64_t)a.y*a.y; }

template<typename T>
int sgn(T x) { return int(x > 0) - int(x < 0); }
int64_t ori(vec2d a, vec2d b, vec2d c) { return (b - a) ^ (c - a); }

vector<vec2d> find_convex_hull(vector<vec2d> points)
{
    auto it = min_element(points.begin(), points.end(), [](vec2d a, vec2d b) {
        return make_pair(a.x, a.y) < make_pair(b.x, b.y);
    });
    swap(points.front(), *it);
    auto s = points.front();
    sort(points.begin()+1, points.end(), [s](vec2d a, vec2d b) {
        auto v = (a - s) ^ (b - s);
        return v == 0 ? +(a - s) > +(b - s) : v > 0;
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

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<vec2d> P(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> P[i].x >> P[i].y;
    P = find_convex_hull(P); n = P.size();

    uint32_t i = 0;
    int64_t result = 0;
    auto dist_cmp = [&](vec2d a, vec2d b) { return +(a-P[i]) < +(b-P[i]); };
    for(uint32_t j = max_element(P.begin(), P.end(), dist_cmp) - P.begin();
        i < n; i++)
    {
        uint32_t j1 = (j==n-1 ? 0 : j+1);
        while(j1 != i and dist_cmp(P[j], P[j1]))
            j = j1, j1 = (j==n-1 ? 0 : j+1);
        result = max(result, +(P[i]-P[j]));
    }
    cout << result;
}
