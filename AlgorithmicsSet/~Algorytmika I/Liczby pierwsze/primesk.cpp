#include <bits/stdc++.h>
#include <ktl/math/primality.cpp>

using namespace std;

int main()
{
    size_t n;
    cin >> n;
    while(n --> 0)
    {
        uint64_t a;
        cin >> a;
        cout << (is_prime(a) ? "TAK" : "NIE") << '\n';
    }
}
