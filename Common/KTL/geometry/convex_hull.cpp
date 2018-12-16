#pragma once

#include <algorithm>
#include <utility>
#include <vector>
#include "vec2d.cpp"

using std::min_element; using std::swap; using std::sort;
using std::vector; using std::make_pair;

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
