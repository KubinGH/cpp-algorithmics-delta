#include <bits/stdc++.h>

using namespace std;

const uint MOD = 1e9 + 7;

int main()
{
    size_t n; int S;
    cin >> n >> S;

    n--;
    if(abs(S) > n*(n+1) / 2)
    {
        cout << '0';
        return 0;
    }

    static uint c[1<<8][1<<18];
    const size_t FIX = 1 << 17;

    auto C = [&](size_t m, int z) -> uint& {
        return c[m][z + FIX];
    };

    C(0, 0) = 1;
    for(int m = 1; m <= (int)n; m++)
        for(int hiss = m*(m+1)/2, z = -hiss; z <= hiss; z++)
            C(m, z) = (C(m-1, z-m) + C(m-1, z+m)) % MOD;

    cout << C(n, S);
}
