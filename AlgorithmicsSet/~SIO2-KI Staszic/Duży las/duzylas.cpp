#include <bits/stdc++.h>
#define mobius(x)                                       \
    ((x) == 1 ? 1ll :                                   \
     (has_square[x] ? 0ll :                             \
      ((is_prime[x] or factors[x]) ? -1ll : 1ll)))

using namespace std;

const size_t MAX = 1e7+1;

int main()
{
    int64_t n, m;
    cin >> n >> m;
    if(n < m) swap(n, m);
    static bitset<MAX> factors, is_prime, has_square;
    is_prime.set();
    is_prime[0] = is_prime[1] = false;
    for(uint32_t i = 2; i <= (uint32_t)n; i++)
    {
        if(not is_prime[i])
            continue;
        for(uint32_t x = 2*i; x <= (uint32_t)n; x += i)
        {
            factors.flip(x);
            is_prime[x] = false;
            if(x % (i*i) == 0)
                has_square[x] = true;
        }
    }
    int64_t r = 2;
    for(int64_t d = 1; d <= n; d++)
    {
        r += mobius(d) * (n/d) * (m/d);
    }
    cout << r;
}
