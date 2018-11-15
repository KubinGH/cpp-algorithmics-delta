#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t a, b, c;
    cin >> a >> b >> c;
    uint64_t f = 1;
    for(uint64_t i = b+1; i <= a; i++)
    {
        f *= i%c; f %= c;
        if(f == 0)
            break;
    }
    cout << f;
}
