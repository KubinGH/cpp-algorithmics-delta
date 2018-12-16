#pragma once

#include <bits/stdc++.h>

using namespace std;

template<typename T>
using point_t = complex<T>;
#define X real()
#define Y imag()

// Dot product
template<typename T>
T cross(const point_t<T>& a, const point_t<T>& b)
{
    return a.X * b.Y - a.Y * b.X;
}

int64_t sign(int64_t x) { return (x >= 0) - (x <= 0); }

// orientation of triplet [triangle] (a, b, c)
// = 0 if colinear
// > 0 clockwise
// < 0 counterclockwise
template<typename T>
T ori(const point_t<T>& a, const point_t<T>& b, const point_t<T>& c)
{
    return sign((c.Y-a.Y) * (b.X-a.X) - (b.Y-a.Y) * (c.X-a.X));
}

// on segment
// point p is on segment |ab|
template<typename T>
bool ons(const point_t<T>& a, const point_t<T>& b, const point_t<T>& p)
{
    return (b.X <= max(a.X, p.X) and b.X >= min(a.X, p.X) and
            b.Y <= max(a.Y, p.Y) and b.Y >= min(a.Y, p.Y));
}

template<typename T>
bool intersects(const point_t<T>& a, const point_t<T>& b,
                const point_t<T>& c, const point_t<T>& d)
{
    int64_t o1 = ori(a, b, c), o2 = ori(a, b, d),
            o3 = ori(c, d, a), o4 = ori(c, d, b);
    if(o1 != o2 and o3 != o4)
        return true;
    else if((o1 == 0 and ons(a, c, b)) or
            (o2 == 0 and ons(a, d, b)) or
            (o3 == 0 and ons(c, a, d)) or
            (o4 == 0 and ons(c, b, d)))
        return true;
    else
        return false;
}

// Double, oriented area
// (+ccw, -cw)
// use abs(polygon.area)/2 for actual value
template<typename T>
T area(const vector<point_t<T>>& polygon)
{
    T result = 0;
    size_t prev_i = polygon.size() - 1, next_i = 1;
    for(size_t i = 0; i < polygon.size(); i++)
    {
        result += polygon[i].X * (polygon[prev_i].Y - polygon[next_i].Y);
        prev_i = i;
        next_i = i+1;
        if(next_i == polygon.size()) next_i = 0;
    }
    return result;
}

// Convex hull
// Andrew's monotone chain algorithm
template<typename T, bool INCLUDE_COLINEAR = true>
vector<point_t<T>> convex_hull(vector<point_t<T>>& points)
{
    sort(
         points.begin(), points.end(),
         [](const point_t<T>& lhs, const point_t<T>& rhs) {
            return lhs.X < rhs.X or (lhs.X == rhs.X and lhs.Y < rhs.Y);
    });
    vector<point_t<T>> hull; hull.reserve(points.size());
    for(uint32_t phase = 0; phase < 2; phase++)
    {
        size_t start = hull.size();
        for(const point_t<T>& point : points)
        {
            while(
                hull.size() >= start + 2 and
                (INCLUDE_COLINEAR
                ? (ori(point, hull[hull.size()-1], hull[hull.size()-2]) <= 0)
                : (ori(point, hull[hull.size()-1], hull[hull.size()-2]) < 0))
            ) hull.pop_back();
            hull.push_back(point);
        }
        hull.pop_back();
        reverse(points.begin(), points.end());
    }
    if(hull.size() == 2 and hull[0] == hull[1]) hull.pop_back();
    return hull;
}
