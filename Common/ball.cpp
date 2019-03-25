#include <bits/stdc++.h>
#include "KTL/math/simpson.cpp"

using namespace std;

int main()
{
    cout << fixed << setprecision(10);
    cout << acos(-1.0) * 4.0/3.0 << endl;
    auto circle_area = [&](double r) {
        return 4 * simpson_integration([&](double x) { return sqrt(r*r - x*x); }, 0.0, r, 4e4);
    };
    auto ball_volume = [&](double R) {
        return 2 * simpson_integration([&](double h) { return circle_area(sqrt(R*R - h*h)); }, 0.0, R, 4e4);
    };
    cout << ball_volume(1);
}
