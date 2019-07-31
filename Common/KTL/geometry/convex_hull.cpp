// Convex hull via Graham Scan
// Complexity: O(n log n)
// Last revision: Beginning of 2019

#pragma once

#include <algorithm>
#include <utility>
#include <vector>
#include "vec2d.cpp"

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
