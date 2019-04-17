#include <bits/stdc++.h>


#include <cstdint>
#include <cmath>

using std::size_t;
using std::abs;

template<typename T, typename Function>
T simpson_integration(Function f, T a, T b, size_t n)
{
    T h = (b - a) / (2 * n);
    T s = f(a) + f(b);
    for(size_t i = 1; i < 2 * n; i++)
    {
        T x = a + h * i;
        s += f(x) * (i%2 ? 4 : 2);
    }
    return s * (h / 3);
}

template<typename T, typename Function>
T extended_simpson_integration(Function f, T a, T b, size_t n, T eps)
{
    T h = (b - a) / (2 * n);
    T s = f(a) + f(b);
    for(size_t i = 1; i < 2 * n; i++)
    {
        T x = a + h * i;
        s += f(x) * (i%2 ? 4 : 2);
    }
    auto left = simpson_integration(f, a, (a+b)/2, n),
        right = simpson_integration(f, (a+b)/2, b, n);
    auto result = s * (h / 3);
    if(abs((left + right) - result) > eps)
        return extended_simpson_integration(f, a, (a+b)/2, n, eps)
             + extended_simpson_integration(f, (a+b)/2, b, n, eps);
    else
        return result;
}


template<typename T, typename Function>
T simpson_integration(Function, T, T, size_t);
template<typename T, typename Function>
T extended_simpson_integration(Function, T, T, size_t, T);

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
        return 4 * extended_simpson_integration([&](long double x) { return sqrt(r*r - x*x); }, 0.0L, r, 100, 1e-10L);
    };
    auto ball_volume2 = [&](long double R) {
        return 2 * extended_simpson_integration([&](long double h) { return circle_area2(sqrt(R*R - h*h)); }, 0.0L, R, 1000, 1e-10L);
    };
    cout << (double)ball_volume(2) << endl;
    cout << (double)ball_volume2(2) << endl;
}
