#include <cstdint>
#include <iostream>

using std::int64_t; using std::istream;

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
}
