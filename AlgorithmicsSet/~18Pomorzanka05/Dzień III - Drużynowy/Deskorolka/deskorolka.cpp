#include <bits/stdc++.h>

using namespace std;

const double g = 10, m = 2, M = 44.5;

int main()
{
    double d, h;
    cin >> d >> h;
    cout << fixed << setprecision(3);
    double t = sqrt(2*h/g), v1 = d/t, v2 = m*v1/M;
    double W = M*v2*v2/2 + m*v1*v1/2;
    cout << W;
}
