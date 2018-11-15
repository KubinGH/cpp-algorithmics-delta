#include <bits/stdc++.h>

using namespace std;

// N >= max(sqrt(last), last - first)
template<typename T, size_t N>
struct eratosthenes_sieve
{
    T first, last;
    bitset<N> is_prime_base;
    uint32_t omega[N];
    eratosthenes_sieve(T first, T last) : first(first), last(last)
    {
        T up = ceil(sqrt(last))+1;
        is_prime_base.set();
        fill(omega, omega + (last-first), 0);
        static uint64_t X[N];
        iota(X, X + (last-first), first);
        for(T i = 2; i*i <= last; i += 2)
        {
            if(not is_prime_base[i])
                continue;
            for(T x = i*i; x < up; x += i)
                is_prime_base[x] = false;
            for(T x = ((first+i-1) / i) * i; x < last; x += i)
            {
                while(X[x - first] % i == 0)
                    omega[x - first]++, X[x - first] /= i;
            }
            if(i == 2) i--;
        }
        for(size_t i = 0; i < last - first; i++)
            if(X[i] > 1) omega[i]++;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t a; uint32_t k;
    cin >> a >> k;
    static eratosthenes_sieve<uint64_t, 1u << 21> sieve(a, a + (k+7));
    uint64_t c = a; uint32_t total_omega = 0;
    while(total_omega < k)
    {
        total_omega += sieve.omega[c - sieve.first];
        c++;
    }
    c--; total_omega -= sieve.omega[c - sieve.first];
    vector<uint64_t> F; F.reserve(64);
    uint64_t d = c;
    for(uint64_t i = 2; i * i <= c; i++)
        while(d % i == 0) d /= i, F.push_back(i);
    if(d > 1) F.push_back(d), d = 1;
    sort(F.begin(), F.end());
    cout << F[k - total_omega - 1];
}
