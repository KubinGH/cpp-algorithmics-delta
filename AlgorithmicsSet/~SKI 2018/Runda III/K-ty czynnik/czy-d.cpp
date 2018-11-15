#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct eratosthenes_sieve
{
    T first, last;
    vector<bool> is_prime_base;
    vector<uint32_t> omega;
    eratosthenes_sieve(T first, T last) : first(first), last(last)
    {
        T up = ceil(sqrt(last))+1;
        is_prime_base.resize(up, true);
        omega.resize(last - first);
        vector<uint64_t> X(last - first);
        iota(X.begin(), X.end(), first);
        for(T i = 2; i*i <= last; i += 2)
        {
            if(not is_prime_base[i])
                continue;
            for(T x = 2*i; x < up; x += i)
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

template<typename T>
T kfactor(T a, uint32_t k)
{
    eratosthenes_sieve<uint64_t> sieve(a, a + (k+7));
    uint64_t c = a; uint32_t total_omega = 0;
    while(total_omega < k)
    {
        total_omega += sieve.omega[c - sieve.first];
        c++;
    }
    c--; total_omega -= sieve.omega[c - sieve.first];
    vector<uint64_t> F;
    uint64_t d = c;
    for(uint64_t i = 2; i * i <= c; i++)
        while(d % i == 0) d /= i, F.push_back(i);
    if(d > 1) F.push_back(d), d = 1;
    sort(F.begin(), F.end());
    return F[k - total_omega - 1];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t a; uint32_t k;
    cin >> a >> k;
    cout << kfactor(a, k);
}
