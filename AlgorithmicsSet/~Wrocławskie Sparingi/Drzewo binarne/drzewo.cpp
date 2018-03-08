#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t q;
    cin >> q;
    for(uint32_t qi = 0; qi < q; qi++)
    {
        uint64_t a, b;
        cin >> a >> b;
        if(a > b) swap(a, b);
        uint64_t u = 64 - __builtin_clzll(a), v = 64 - __builtin_clzll(b);
        uint64_t r = v - u;
        b >>= (v - u);
        while(a != b)
        {
            a /= 2; b /= 2;
            r += 2;
        }
        cout << r << '\n';
    }
}
