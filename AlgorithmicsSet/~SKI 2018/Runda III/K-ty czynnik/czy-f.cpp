#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct eratosthenes_sieve
{
    T first, last;
    vector<bool> is_prime_base, is_prime;
    vector<vector<T>> factors;
    eratosthenes_sieve(T first, T last) : first(first), last(last)
    {
        T up = ceil(sqrt(last))+1;
        is_prime_base.resize(up*2, true);
        is_prime.resize(last - first, true);
        factors.resize(last - first);
        for(T i = 2; i*i <= last; i += 2)
        {
            if(not is_prime_base[i])
                continue;
            for(T x = 2*i; x < up; x += i)
                is_prime_base[x] = false;
            for(T x = ((first+i-1) / i) * i; x < last; x += i)
                if(x >= first)
                    factors[x - first].push_back(i), is_prime[x - first] = false;
            if(i == 2) i--;
        }
        for(T i = first; i < last; i++)
        {
            T j = i;
            for(T p : factors[i - first])
                while(j % p == 0) j /= p;
            if(j > 1)
            {
                factors[i - first].push_back(j);
                sort(factors[i-first].begin(), factors[i-first].end());
            }
        }
    }
    const vector<T>& operator[] (T x) const { return factors[x - first]; }
};

template<typename T>
T kfactor(T a, uint32_t k)
{
    eratosthenes_sieve<uint64_t> sieve(a, a + (k+7));
    uint64_t c = a; uint32_t total_omega = 0, last_omega = 0;
    while(total_omega < k)
    {
        uint32_t omega = 0;
        uint64_t d = c;
        for(uint64_t p : sieve[c])
            while(d % p == 0)
                omega++, d /= p;
        total_omega += (last_omega = omega);
        c++;
    }
    c--; total_omega -= last_omega;
    vector<uint64_t> F;
    uint64_t d = c;
    for(uint64_t p : sieve[c])
        while(d % p == 0)
            F.push_back(p), d /= p;
    if(d > 1)
        F.push_back(d), d = 1;
    sort(F.begin(), F.end());
    return F[k - total_omega - 1];
}

int main()
{
    uint64_t a; uint32_t k;
    cin >> a >> k;
    cout << kfactor(a, k) << "\n";
}
