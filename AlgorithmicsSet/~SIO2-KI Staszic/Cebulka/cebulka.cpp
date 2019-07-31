#include <bits/stdc++.h>
#include <ktl/geometry/vec2d.cpp>
#include <ktl/geometry/convex_hull.cpp>

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
