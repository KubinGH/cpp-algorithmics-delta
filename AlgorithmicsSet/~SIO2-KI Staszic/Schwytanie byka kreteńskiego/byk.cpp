#include <bits/stdc++.h>

using namespace std;

int main()
{
    uint32_t n;
    cin >> n;
    long double s = 0, v = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        long double a, t;
        cin >> a >> t;
        s += v*t + a/2*t*t;
        v += a*t;
    }
    cout.precision(2); cout.setf(ios::fixed);
    cout << abs(v) << " " << abs(s);
}
