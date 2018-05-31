#include <bits/stdc++.h>

using namespace std;

int main()
{
    uint32_t n, m;
    cin >> n >> m;
    // r = (n - m) / n
    uint32_t g = __gcd(n - m, n);
    cout << (n-m)/g << "/" << n/g;
}
