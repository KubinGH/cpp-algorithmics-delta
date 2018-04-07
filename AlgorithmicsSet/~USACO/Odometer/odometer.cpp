#include <bits/stdc++.h>

using namespace std;

const size_t DIG = 16;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    //ifstream cin("odometer.in");
    //ofstream cout("odometer.out");
    uint64_t x, y;
    cin >> x >> y;
    static array<uint64_t, DIG> POW10;
    POW10[0] = 1;
    for(uint64_t i = 1; i < DIG; i++)
        POW10[i] = POW10[i-1] * 10;
    uint64_t result = 0;
    for(uint64_t i = 0, base = 1; i < DIG; i++, base *= 10, base++)
    {
        if(i < 2)
            continue;
        for(uint64_t f = 1; f < 10; f++)
        {
            uint64_t current = f * base;
            for(uint64_t j = 0; j < i + 1; j++)
            {
                for(uint64_t k = 0; k < 10; k++)
                {
                    if(f == k or (k == 0 and j == i))
                        continue;
                    uint64_t c = current - POW10[j] * f + POW10[j] * k;
                    if(x <= c and c <= y)
                    {
                        result++;
                    }
                }
            }
        }
        for(uint64_t k = 1; k < 10; k++)
        {
            if(x <= POW10[i] * k and POW10[i] * k <= y)
                result++;
        }
    }
    if(y == POW10[15] * 10)
        result++;
    cout << result;
}
