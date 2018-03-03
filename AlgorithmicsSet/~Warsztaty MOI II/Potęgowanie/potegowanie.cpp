#include <bits/stdc++.h>

using namespace std;

const uint64_t LIM = 1e7 + 7;

int main()
{
    uint32_t q;
    cin >> q;
    for(uint32_t i = 0; i < q; i++)
    {
        uint64_t a, b;
        cin >> a >> b;
        uint64_t r = 1;
        while(b)
        {
            if(b % 2)
                r *= a, r %= LIM;
            a *= a; a %= LIM;
            b /= 2;
        }
        cout << r << '\n';
    }
}
