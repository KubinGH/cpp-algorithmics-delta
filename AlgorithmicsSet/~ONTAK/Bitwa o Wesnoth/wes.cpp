#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

long double choose(int n, int k)
{
    if(k > n-k) return choose(n, n-k);
    long double f = 1, g = 1;
    for(int i = 1; i <= k; i++)
        g *= i;
    for(int i = n-k+1; i <= n; i++)
        f *= i;
    return f / g;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int m, p;
    cin >> m >> p;

    long double p1 = (long double)p / 100, p0 = 1 - p1;

    size_t n;
    cin >> n;

    cout << fixed << setprecision(5);
    while(n --> 0)
    {
        int h;
        cin >> h;

        tuple<long double, int, int> result {0, 0, 0};
        for(int d1 = 1, d; d1 <= m; d1 = d + 1)
        {
            d = m / (m / d1);
            auto b = m / d;
            long double r = 0;
            for(int k = (h+d-1)/d; k <= b; k++)
            {
                long double a;
                if(k < 50 or b-k < 50)
                    a = choose(b, k) * (pow(p1, k) * pow(p0, b-k));
                else
                    a = power(b*p1/k, k) * power(b*p0/(b-k), b-k) * sqrt((long double)b / (k * (b - k) * 2 * M_PI));
                r += a;
            }
            result = max(result, make_tuple(r, d, b));
        }

        cout << get<1>(result) << ' ' << get<2>(result) << '\n';
    }
}
