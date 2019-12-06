#include <bits/stdc++.h>
#include <ktl/geometry/vec2d.cpp>
#include <ktl/math/gaussian_elimination.cpp>
#include <ktl/structures/fenwick.cpp>

using namespace std;

using num = long double;

struct Point
{
    num x, y;
};
Point to_point(vec2d v) { return Point{num(v.x), num(v.y)}; }

struct Parabola
{
    num a, b, c;
    num operator() (num x) const { return c + x*(b + x*a); }
};
Parabola operator+ (const Parabola& p, const Parabola& q) { return {p.a + q.a, p.b + q.b, p.c + q.c}; }
Parabola operator- (const Parabola& p) { return {-p.a, -p.b, -p.c}; }
Parabola operator- (const Parabola& p, const Parabola& q) { return p + (-q); }

struct Line
{
    num a, b;
    num operator() (num x) const { return a*x + b; }
    operator Parabola() const { return {0, a, b}; }
};
Line operator+ (const Line& p, const Line& q) { return {p.a + q.a, p.b + q.b }; }
Line operator- (const Line& p) { return {-p.a, -p.b}; }
Line operator- (const Line& p, const Line& q) { return p + (-q); }
Line& operator+= (Line& p, const Line& q) { return p = p + q; }
Line& operator-= (Line& p, const Line& q) { return p = p - q; }
Parabola operator~ (const Line& p) { return Parabola{p.a/2, p.b, (num)0}; }

Line interpolate(Point A, Point B)
{
    vector<vector<num>> eq = {
        {A.x, 1, A.y},
        {B.x, 1, B.y}
    };
    auto sol = solve_system_of_linear_equations(eq).second;
    return {sol[0], sol[1]};
}

Parabola interpolate(Point A, Point B, Point C)
{
    vector<vector<num>> eq = {
        {A.x*A.x, A.x, 1, A.y},
        {B.x*B.x, B.x, 1, B.y},
        {C.x*C.x, C.x, 1, C.y}
    };
    auto sol = solve_system_of_linear_equations(eq).second;
    return {sol[0], sol[1], sol[2]};
}

int main()
{
    size_t n, L;
    cin >> n >> L;

    vector<vec2d> P(n);
    for(auto& p : P)
        cin >> p.x >> p.y;
    P.push_back(P.front());

    static Line S[1 << 18];
    for(size_t i = 0; i < n; i++)
    {
        if(P[i].x == P[i+1].x)
            continue;
        auto l = interpolate(to_point(P[i]), to_point(P[i+1]));
        size_t x1, x2;
        if(P[i].x < P[i+1].x)
            l = -l, x1 = P[i].x, x2 = P[i+1].x;
        else
            x1 = P[i+1].x, x2 = P[i].x;
        cout << l.a << ";" << l.b << endl;
        S[x1+(1<<17)] += l;
        S[x2+1+(1<<17)] -= l;
    }

    num result = 0;
    Line s = {0, 0}, z = {0, 0};
    for(size_t x = 0; x < L; x++)
        s += S[x];
    for(size_t x = L; x < (1 << 18); x++)
    {
        s += S[x];
        if(abs(s.a)>1e-9 or abs(s.b)>1e-9)
            cout << int(x-L-(1<<17)) << ".." << int(x-(1<<17)) << " -> " << s.a << ";" << s.b << endl;
        auto para = (~s)(x) - (~z)(x-L);
        result = max({
            result,
            para(x),
            para(para.b/2),
            para(x+1)
        });
        s1 = s;
        z += S[x-L];
    }
    cout << result;
}


/*
        Lawful      Neutral     Chaotic
Good    ?           Jonasz      Jerzy
Neutral Ryszard     Piotr M     Daniel
Evil    ?           Piotr G     Maciek
Chaotic Chaotic Daniel

*/
