#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e7+17;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t n;
    cin >> n;
    uint64_t m = floor(sqrt(n));
    static bitset<MAX> is_composite, has_primesquare, primediv_parity;
    for(uint32_t i = 2; i <= m; i += 2)
    {
        if(is_composite[i]) continue;
        for(uint32_t x = 2*i; x <= m; x += i)
        {
            is_composite[x] = true;
            if(not is_composite[i] and x % (i*i) == 0)
                has_primesquare[x] = true;
            if(not is_composite[i])
                primediv_parity.flip(x);
        }
        if(i == 2) i--;
    }
    auto mobius = [&](uint32_t k) {
        if(k == 1)
            return 1;
        else if(has_primesquare[k])
            return 0;
        else if(primediv_parity[k] ^ is_composite[k])
            return 1;
        else
            return -1;
    };
    uint64_t r = 0;
    for(uint64_t d = 1; d * d <= n; d++)
        r += (n / (d*d)) * mobius(d);
    cout << r;
}
