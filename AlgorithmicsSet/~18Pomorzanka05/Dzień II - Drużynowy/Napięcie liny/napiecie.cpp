#include <bits/stdc++.h>

using namespace std;

const long double g = 9.81;

int main()
{
    long double m, a;
    cin >> m >> a;
    cout << fixed << setprecision(2);
    cout << m*a + m*g;
}
