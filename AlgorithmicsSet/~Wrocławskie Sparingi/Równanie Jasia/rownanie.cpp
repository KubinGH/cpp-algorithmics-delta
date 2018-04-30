#include <bits/stdc++.h>

using namespace std;

const size_t PRIMES = 5e6, PRIME_COUNT = 4e5;

uint64_t gn;
vector<uint64_t> n_primes;
array<uint64_t, 64> Q;
uint32_t qi = 0;

vector<uint64_t> get_divs_p(uint64_t n)
{
    vector<uint64_t> result;
    static array<uint64_t, 64> J; J.fill(0);
    static array<uint64_t, 64> L; L.fill(0);
    uint64_t t = gn / n; uint32_t i = 0;
    for(uint64_t p : n_primes)
    {
        while(t % p == 0)
            J[i]++, L[i]++, t /= p;
        i++;
    }
    while(L[qi] == 0)
    {
        uint64_t d = 1;
        for(uint32_t i = 0; i < qi; i++)
            for(uint32_t j = 0; j < L[i] - J[i]; j++)
                d *= n_primes[i];
        result.push_back(d);
        L[0]++;
        for(uint32_t i = 0; i < qi; i++)
        {
            if(L[i] > Q[i])
            {
                L[i] = J[i];
                L[i+1]++;
            }
        }
    }
    sort(result.begin(), result.end());
    return result;
}

uint64_t div_count_p(uint64_t n)
{
    static array<uint64_t, 64> J; J.fill(0);
    uint64_t t = gn / n; uint32_t i = 0;
    for(uint64_t p : n_primes)
    {
        while(t % p == 0)
            J[i]++, t /= p;
        i++;
    }
    uint64_t r = 1;
    for(uint32_t i = 0; i < qi; i++)
        r *= Q[i] - J[i] + 1;
    return r;
}

int main()
{
    vector<uint64_t> all_primes;
    static bitset<PRIMES> P; P.set();
    for(uint64_t i = 4; i < PRIMES; i += 2)
        P[i] = false;
    all_primes.push_back(2);
    for(uint64_t i = 3; i < PRIMES; i += 2)
    {
        if(not P[i])
            continue;
        for(uint64_t x = i*i; x < PRIMES; x += i)
            P[x] = false;
        all_primes.push_back(i);
    }
    uint64_t n, k;
    cin >> n >> k; gn = n;
    uint64_t t = n;
    for(uint64_t p : all_primes)
    {
        if(t % p == 0)
        {
            n_primes.push_back(p);
            while(t % p == 0)
                t /= p, Q[qi]++;
            qi++;
        }
    }
    if(t > 1)
        n_primes.push_back(t), Q[qi++]++;
    uint64_t p = 0;
    for(uint64_t a : get_divs_p(n))
    {
        for(uint64_t b : get_divs_p(n / a))
        {
            uint64_t h = div_count_p(n / (a*b));
            if(p + h < k)
            {
                p += h;
                continue;
            }
            for(uint64_t c : get_divs_p(n / (a*b)))
            {
                uint64_t d = n / (a*b*c);
                p++;
                if(p == k)
                {
                    cout << a << " " << b << " " << c << " " << d;
                    return 0;
                }
            }
        }
    }
    if(p < k)
    {
        cout << "NIE";
    }
}
