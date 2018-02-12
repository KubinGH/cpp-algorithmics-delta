#include <bits/stdc++.h>

using namespace std;

typedef pair<uint32_t, uint32_t> pair_u32;

const size_t MAX = 6.7e7+1;
const uint32_t MAX_SQRT = ceil(sqrt(MAX)) + 1;

const uint32_t memo[][2] = {
    {191912784, 246}, {189695660, 232},
    {122164748, 220}, {47326694, 218},
    {20831324, 210}
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    if(n >= MAX)
    {
        for(uint32_t i = 0; i < sizeof(memo) / 8 - 1; i++)
        {
            uint32_t a = memo[i][0], b = memo[i][0] + memo[i][1];
            if(n >= b)
            {
                cout << a << " " << b;
                return 0;
            }
            else if(n >= a and n - a > memo[i+1][1])
            {
                cout << a << " " << n;
                return 0;
            }
        }
        n = MAX - 1;
    }
    static bitset<MAX> P;
    P.set();
    P[0] = true; P[1] = true;
    uint32_t s = 4, r = 0, p = 2;
    for(uint32_t x = 4; x <= n; x += 2)
        P[x] = false;
    for(uint32_t i = 3; i <= n; i += 2)
    {
        if(not P[i])
            continue;
        if(i <= MAX_SQRT) for(uint32_t x = i*i; x <= n; x += 2*i)
            P[x] = false;
        if(i > 3 and i >= p + 2 and i - p - 2 > r)
            s = p+1, r = i - p - 2;
        p = i;
    }
    if(n >= p + 1 and n - p - 1 > r)
        s = p+1, r = n - p - 1;
    cout << s << " " << s + r;
}
