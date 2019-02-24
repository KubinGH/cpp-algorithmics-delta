#include <bits/stdc++.h>

using namespace std;

struct vec2d { int32_t x, y; };
vec2d operator+ (vec2d a, vec2d b) { return {a.x+b.x, a.y+b.y}; }
vec2d operator- (vec2d a) { return {-a.x, -a.y}; }
vec2d operator- (vec2d a, vec2d b) { return a + (-b); }
int64_t operator* (vec2d a, vec2d b) { return (int64_t)a.x*b.x + (int64_t)a.y*b.y; }
int64_t operator^ (vec2d a, vec2d b) { return (int64_t)a.x*b.y - (int64_t)a.y*b.x; }
int64_t operator+ (vec2d a) { return (int64_t)a.x*a.x + (int64_t)a.y*a.y; }

template<typename T>
int sgn(T x) { return x < 0 ? -1 : x > 0; }
int ori(vec2d a, vec2d b, vec2d c) { return sgn((b - a) ^ (c - a)); }

struct segment2d { vec2d A, B; };

istream& operator>> (istream& in, vec2d& v) { return in >> v.x >> v.y; }
istream& operator>> (istream& in, segment2d& v) { return in >> v.A >> v.B; }

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

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    while(n --> 0)
    {
        segment2d P, Q;
        cin >> P >> Q;
        cout << (intersects(P, Q) ? "TAK\n" : "NIE\n");
    }
}
