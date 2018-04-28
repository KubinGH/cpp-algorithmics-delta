#include <bits/stdc++.h>

using namespace std;

int main()
{
    double y1, x1, y2, x2;
    cin >> y1 >> x1 >> y2 >> x2;
    double p1 = x1 * y1 / 2, p2 = x2 * y2 / 2;
    double a = sqrt(x1*x1 + y1*y1), b = sqrt(x2*x2 + y2*y2);
    cout << fixed << setprecision(3);
    cout << min((2*p1) / (x1+y1+a), (p1 / a) - (p2 / b));
}
