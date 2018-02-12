#include <bits/stdc++.h>

using namespace std;

int main()
{
    uint64_t p, q;
    cin >> p >> q;
    uint64_t g = __gcd(p, q);
    if(g == p or g == q)
        cout << "NIESKONCZONOSC";
    uint64_t v = p * q - p - q;
    if(v == 0)
        cout << "ZADEN";
    else
        cout << v;
}
