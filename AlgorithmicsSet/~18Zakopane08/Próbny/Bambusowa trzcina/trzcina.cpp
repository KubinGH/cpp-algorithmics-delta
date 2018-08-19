#include <bits/stdc++.h>

using namespace std;

int main()
{
    double h, d;
    cin >> h >> d;
    cout << fixed << setprecision(2) << (h - d*d/h)/2;
}
