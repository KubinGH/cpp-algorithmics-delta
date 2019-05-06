// Segment-related geometry.
// Segment intersection is strict.
// Last revision: March 2019

#pragma once

#include <algorithm>
#include "vec2d.cpp"

using std::min; using std::max;

struct segment2d { vec2d A, B; };

bool ons(const vec2d& A, const vec2d& B, const vec2d& P)
{
    return ori(A, B, P) == 0 and
           min(A.x, B.x) <= P.x and P.x <= max(A.x, B.x) and
           min(A.y, B.y) <= P.y and P.y <= max(A.y, B.y);
}
bool intersects(const segment2d& P, const segment2d& Q)
{
    int p1 = ori(P.A, P.B, Q.A), p2 = ori(P.A, P.B, Q.B),
        q1 = ori(Q.A, Q.B, P.A), q2 = ori(Q.A, Q.B, P.B);
    if(p1 != p2 and q1 != q2)
        return true;
    else if(ons(P.A, P.B, Q.A) or ons(P.A, P.B, Q.B) or
            ons(Q.A, Q.B, P.A) or ons(Q.A, Q.B, P.B))
        return true;
    else
        return false;
}
