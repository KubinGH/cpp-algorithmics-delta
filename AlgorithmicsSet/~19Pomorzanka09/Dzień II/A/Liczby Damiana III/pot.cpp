#include <bits/stdc++.h>
#ifdef XHOVA
#define cdbg cerr
#else
#define cdbg if(0) cerr
#endif

using namespace std;

struct prime_cache
{
    vector<bool> sieve;
    vector<int> list;
    prime_cache(int n) : sieve(n, true)
    {
        for(int p = 2; p < n; p++)
        {
            if(sieve[p])
            {
                list.push_back(p);
                if(p < (1<<15)) for(int x = p*p; x < n; x += p)
                    sieve[x] = false;
            }
        }

    }
} primes(1 << 19);

struct pint
{
    unordered_map<int, int> factors;

    pint() {}
    pint(int n)
    {
        factors.reserve(16);
        int on = n;
        for(auto p : primes.list)
        {
            if((int64_t)p*p > on) break;
            while(n % p == 0)
                factors[p]++, n /= p;
        }
        if(n > 1) factors[n]++;
    }

    friend pint operator* (const pint& a, const pint& b)
    {
        pint r = a;
        for(auto p : b.factors)
            r.factors[p.first] += p.second;
        return r;
    }
    friend pint operator^ (const pint& a, int e)
    {
        pint r = a;
        for(auto& p : r.factors)
            p.second *= e;
        return r;
    }

    int exponent_gcd() const
    {
        int d = 0;
        for(auto p : factors)
            d = __gcd(d, p.second);
        return d;
    }
    vector<int> exponents() const
    {
        vector<int> r;
        for(auto p : factors)
            r.push_back(p.second);
        return r;
    }

    pint operator! () const
    {
        pint r = *this;
        auto d = r.exponent_gcd();
        for(auto& p : r.factors)
            p.second /= d;
        return r;
    }

    int64_t sigma() const
    {
        int64_t r = 1;
        for(auto p : factors)
            r *= p.second + 1;
        return r;
    }
};

int64_t rho_cache[1 << 20];
int64_t rho(int a)
{
    if(rho_cache[a]) return rho_cache[a];

    int64_t result = 0;
    auto d = pint(a).exponent_gcd();
    for(int k = 1; k <= d; k++)
        if(d % k == 0)
            result += rho(k);

    return rho_cache[a] = result;
}

int main()
{
    rho_cache[1] = 1;

    size_t T;
    cin >> T;
    while(T --> 0)
    {
        int ai, bi, ci;
        scanf("%d^%d^%d", &ai, &bi, &ci);
        pint a = ai, b = bi, c = ci;
        pint B = b ^ ci;
        tie(a, B) = make_pair(!a, B * a.exponent_gcd());

        auto X = B.exponents();

        auto dax = *max_element(X.begin(), X.end()) + 2;
        vector<int64_t> D(dax);
        for(int d = dax; d --> 1; )
        {
            D[d] = 1;
            for(int i = 0; i < (int)X.size(); i++)
                D[d] *= X[i]/d + 1;
            D[d]--;
        }

        int64_t r = -B.sigma()+1;
        for(int i = 1; i < dax; i++)
            r += rho(i) * D[i];
        cout << r << endl;
    }
}
