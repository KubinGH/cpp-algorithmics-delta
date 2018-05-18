#include <bits/stdc++.h>

using namespace std;

int main()
{
    double a, b, c;
    cin >> a >> b >> c;
    cout << fixed << setprecision(3);
    cout << 3 * (a*b*c) / (a*b + a*c + b*c);
}
