#include <bits/stdc++.h>
#ifdef XHOVA
#define cdbg cerr
#else
#define cdbg if(0) cerr
#endif

using namespace std;

struct prime_cache
{
    vector<int> list;
    prime_cache(int64_t n)
    {
        for(int p = 2; p <= n; p++)
        {
            bool ok = true;
            for(int d = 2; d < (1 << 15) and d*d <= p and ok; d++)
                if(p % d == 0)
                    ok = false;
            if(ok)
                list.push_back(p);
        }
    }
} primes(1 << 16);

vector<int> divisors(int n)
{
    vector<int> r;
    for(int d = 1; d < (1 << 15) and d*d <= n; d++)
      if(n % d == 0)
    {
        r.push_back(d);
        if(n != d*d) r.push_back(n / d);
    }
    sort(r.begin(), r.end());
    return r;
}

struct pint
{
    map<int, int> factors;

    pint() {}
    pint(int64_t n)
    {
        for(auto p : primes.list)
            while(n % p == 0)
                factors[p]++, n /= p;
    }

    int64_t to_int() const
    {
        bool of = false;
        int64_t m = 1;
        for(auto p : factors)
        {
            for(int i = 0; i < p.second; i++)
            {
                m *= p.first;
                if(m > (1ll << 36))
                {
                    of = true;
                    break;
                }
            }
        }
        return of ? INT_MAX : m;
    }

    friend istream& operator>> (istream& in, pint& n)
    {
        int64_t i; in >> i; n = pint(i);
        return in;
    }
    friend ostream& operator<< (ostream& out, const pint& n)
    {
        if(n.factors.empty())
            return out << "(1)";
        bool init = true;
        out << "(";
        for(auto p : n.factors)
        {
            if(not init) out << " * ";
            else init = false;
            out << p.first << "^" << p.second;
        }
        out << " = ";
        auto m = n.to_int();
        if(m == INT_MAX) out << "???";
        else             out << m;
        return out << ")";
    }

    friend pint operator* (const pint& a, const pint& b)
    {
        pint r = a;
        for(auto p : b.factors)
            r.factors[p.first] += p.second;
        return r;
    }
    friend pint operator/ (const pint& a, const pint& b)
    {
        pint r = a;
        for(auto p : b.factors)
            r.factors[p.first] -= p.second;
        return r;
    }
    friend pint operator^ (const pint& a, int e)
    {
        pint r = a;
        for(auto& p : r.factors)
            p.second *= e;
        return r;
    }
    pint root(int deg) const
    {
        pint r = *this;
        for(auto& p : r.factors)
            p.second /= deg;
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

map<int64_t, int64_t> cache = {{1, 1}};
int64_t rho(pint a, size_t depth = 0)
{
    auto it = cache.find(a.to_int());
    if(it != cache.end()) return it->second;

    int64_t result = 0;
    for(auto k : divisors(a.exponent_gcd()))
        result += rho(k, depth + 1);

    return cache[a.to_int()] = result;
}

int main()
{
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
        vector<size_t> D(dax);
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
