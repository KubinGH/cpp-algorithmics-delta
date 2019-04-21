// Polygon-related geometry.
// Polygon area via triangle anchored in (0, 0).
// Last revision: March 2019

#pragma once

#include <vector>
#include <cstdint>

#include "vec2d.cpp"

using std::vector; using std::int64_t;

int64_t polygon_area(const vector<vec2d>& vertices)
{
    int64_t result = area({0, 0}, vertices.back(), vertices.front());
    for(uint32_t i = 0; i+1 < vertices.size(); i++)
        result += area({0, 0}, vertices[i], vertices[i+1]);
    return result;
}
