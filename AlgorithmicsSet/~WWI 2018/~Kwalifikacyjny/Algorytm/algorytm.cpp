#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t a, b;
    cin >> a >> b;
    uint64_t r = 0;
    if(a > b)
        swap(a, b);
    while(a != b)
    {
        uint64_t d = b % a;
        if(d == 0) d += a;
        r += (b - d) / a;
        tie(a, b) = make_tuple(d, a);
    }
    cout << r;
}
