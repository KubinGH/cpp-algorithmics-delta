#include <bits/stdc++.h>

using namespace std;

const size_t NAX = 1 << 24, NAX_RT = 1 << 12;

int main()
{
    static bool is_prime[NAX];
    fill(begin(is_prime), end(is_prime), true);
    is_prime[1] = false;
    for(size_t i = 2; i < NAX_RT; i++)
        if(is_prime[i]) for(size_t x = i*i; x < NAX; x += i)
            is_prime[x] = false;

    uint64_t l, r;
    cin >> l >> r;

    unsigned result = 0;
    for(size_t i = 1; i < NAX; i++) if(is_prime[i])
    {
        size_t k = 2;
        uint64_t x = (uint64_t)i * i;
        while(x < l)
            x *= i, k++;
        while(x <= r)
        {
            if(is_prime[k + 1])
                result++;
            x *= i; k++;
        }
    }

    cout << result;
}
