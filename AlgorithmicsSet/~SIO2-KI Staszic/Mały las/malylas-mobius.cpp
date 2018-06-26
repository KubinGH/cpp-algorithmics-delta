#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 5e5+1;

int main()
{
    int64_t n;
    cin >> n;
    static uint32_t factors[MAX];
    static int64_t mobius[MAX];
    fill(mobius, mobius + n+1, 42);
    mobius[1] = 1;
    for(uint32_t i = 2; i <= (uint32_t)n; i++)
    {
        if(mobius[i] == 0)
            ;
        else if(factors[i] != 0 and factors[i] % 2 == 0)
            mobius[i] = 1;
        else
            mobius[i] = -1;
        if(factors[i])
            continue;
        for(uint32_t x = 2*i; x <= (uint32_t)n; x += i)
        {
            factors[x]++;
            if(x % (i*i) == 0)
                mobius[x] = 0;
        }
    }
    int64_t r = 2;
    for(int64_t d = 1; d <= n; d++)
        r += mobius[d] * (n/d) * (n/d);
    cout << r;
}
