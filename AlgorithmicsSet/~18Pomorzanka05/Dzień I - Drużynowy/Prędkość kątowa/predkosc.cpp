#include <bits/stdc++.h>

using namespace std;

int main()
{
    double r, i, m, h;
    cin >> r >> i >> m >> h;
    cout << fixed << setprecision(3);
    cout << sqrt(2*10*(m*r*r)/(m*r*r+i)*h)/r;
}

