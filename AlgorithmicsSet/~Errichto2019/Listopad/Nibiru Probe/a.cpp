#include <bits/stdc++.h>
#include <ktl/math/gaussian_elimination.cpp>

using namespace std;

using num = long double;

struct Point
{
    num x, y;
};

struct Parabola
{
    num a, b, c;
    num operator() (num x) const { return c + x*(b + x*a); }
};

struct Line
{
    num a, b;
    num operator() (num x) const { return a*x + b; }
    operator Parabola() const { return {0, a, b}; }
};

Line interpolate(Point A, Point B)
{
    vector<vector<num>> eq = {{A.x, 1, A.y}, {B.x, 1, B.y}};
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

}


/*
        Lawful      Neutral     Chaotic
Good    ?           Jonasz      Jerzy
Neutral Ryszard     Piotr M     Daniel
Evil    ?           Piotr G     Maciek
Chaotic Chaotic Daniel

*/
