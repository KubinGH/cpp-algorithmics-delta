#include <bits/stdc++.h>

using namespace std;

struct vec2d { int64_t x, y; };
vec2d operator+ (vec2d a, vec2d b) { return {a.x+b.x, a.y+b.y}; }
vec2d operator- (vec2d a) { return {-a.x, -a.y}; }
vec2d operator- (vec2d a, vec2d b) { return a + (-b); }
int64_t operator* (vec2d a, vec2d b) { return a.x*b.x + a.y*b.y; }
int64_t operator^ (vec2d a, vec2d b) { return a.x*b.y - a.y*b.x; }
int64_t operator+ (vec2d a) { return a.x*a.x + a.y*a.y; }
bool operator== (vec2d a, vec2d b) { return a.x == b.x and a.y == b.y; }

template<typename T>
int sgn(T x) { return int(x > 0) - int(x < 0); }
int64_t ori(vec2d a, vec2d b, vec2d c)
    { return (c.y-a.y) * (b.x-a.x) - (b.y-a.y) * (c.x-a.x); }

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

bool on_segment(vec2d a, vec2d b, vec2d p)
{
    return ((a - p) ^ (b - p)) == 0
       and min(a.x,b.x)<=p.x and p.x<=max(a.x,b.x)
       and min(a.y,b.y)<=p.y and p.y<=max(a.y,b.y);
}
bool in_triangle(vec2d a, vec2d b, vec2d c, vec2d p)
{
    uint32_t o1 = sgn(ori(a, b, p))+1, o2 = sgn(ori(b, c, p))+1, o3 = sgn(ori(c, a, p))+1;
    uint32_t m = (1<<o1) | (1<<o2) | (1<<o3);
    return ((m>>2) + (m&1) <= 1) or on_segment(a, b, p) or on_segment(b, c, p) or on_segment(c, a, p);
}

uint32_t solve(const vector<vec2d>& vertices, const vector<vec2d>& points)
{
    if(vertices.size() < 2)
        return 0;
    auto hull = find_convex_hull(vertices);
    uint32_t result = 0;
    for(auto p : points)
    {
        if(hull.size() == 2)
            result += on_segment(hull[0], hull[1], p);
        else if(hull.size() < 50)
        {
            for(uint32_t i = 1; i+1 < hull.size(); i++)
                if(in_triangle(hull[0], hull[i], hull[i+1], p))
                    { result++; break; }
        }
        else
        {
            uint32_t lo = 1, hi = hull.size()-1;
            while(lo < hi)
            {
                uint32_t i = (lo+hi)/2;
                if(sgn(ori(hull[0], hull[i], p)) == -1 and sgn(ori(hull[0], hull[i], p)) == -1)
                    hi = i;
                else
                    lo = i+1;
            }
            lo--;
            if(lo and in_triangle(hull[0], hull[lo], hull[lo+1], p))
                result++;
        }
    }
    return result;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<vec2d> A(n), B(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i].x >> A[i].y;
    for(uint32_t i = 0; i < n; i++)
        cin >> B[i].x >> B[i].y;
    cout << solve(A, B) << " " << solve(B, A);
}
