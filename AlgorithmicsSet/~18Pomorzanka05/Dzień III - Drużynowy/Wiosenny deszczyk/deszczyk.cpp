#include <bits/stdc++.h>

using namespace std;

double c = 4200, g = 10;

int main()
{
    double t, v, x;
    cin >> t >> v >> x;
    cout << fixed << setprecision(3);
    cout << (v*v/2 + (c*t) / (1 - x/100)) / g;
}
