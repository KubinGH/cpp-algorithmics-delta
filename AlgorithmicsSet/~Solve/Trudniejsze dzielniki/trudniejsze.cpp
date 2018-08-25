#include <bits/stdc++.h>

using namespace std;

const uint64_t primes[] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
    43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, -1LLU
};

pair<uint64_t, uint64_t>
find_antiprime(uint64_t m, uint32_t i = 0, uint32_t t = 64)
{
    if(primes[i] > m)
        return {1, 1};
    pair<uint64_t, uint64_t> r = {1, 1};
    uint64_t p = 1;
    for(uint32_t q = 0; q <= t; q++)
    {
        if(p > m)
            break;
        auto o = find_antiprime(m / p, i + 1, q);
        o.first *= q + 1; o.second *= p;
        if(o.first > r.first or (o.first == r.first and o.second < r.second))
            r = o;
        p *= primes[i];
    }
    return r;
}

int main()
{
    uint64_t n;
    cin >> n;
    cout << find_antiprime(n).second;
}
