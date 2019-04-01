#include <bits/stdc++.h>
#include "KTL/math/simpson.cpp"

using namespace std;

int main()
{
    cout << fixed << setprecision(20);
    cout << (double)(acos(-1.0L) * 4.0L/3.0L * 8) << endl;
    auto circle_area = [&](long double r) {
        return 4 * simpson_integration([&](long double x) { return sqrt(r*r - x*x); }, 0.0L, r, 1000);
    };
    auto ball_volume = [&](long double R) {
        return 2 * simpson_integration([&](long double h) { return circle_area(sqrt(R*R - h*h)); }, 0.0L, R, 1000);
    };
    auto circle_area2 = [&](long double r) {
        return 4 * extended_simpson_integration([&](long double x) { return sqrt(r*r - x*x); }, 0.0L, r, 1000, 1e-14L);
    };
    auto ball_volume2 = [&](long double R) {
        return 2 * extended_simpson_integration([&](long double h) { return circle_area2(sqrt(R*R - h*h)); }, 0.0L, R, 1000, 1e-14L);
    };
    cout << (double)ball_volume(2) << endl;
    cout << (double)ball_volume2(2) << endl;
}
