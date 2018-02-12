#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t t;
    cin >> t;
    for(uint32_t p = 0; p < t; p++)
    {
        uint32_t n, d;
        cin >> n >> d;
        cout << n / __gcd(n, d) << '\n';
    }
}
