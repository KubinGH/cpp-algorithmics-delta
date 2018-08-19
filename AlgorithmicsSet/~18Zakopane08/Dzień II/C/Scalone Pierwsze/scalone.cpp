#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 22;

const uint64_t POW10[] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000
};

template<typename T, T B>
T ndigits(T x)
{
    T r = 0;
    while(x) x /= B, r++;
    return r;
}

template<typename T>
bool is_prime_sqrt(T x)
{
    for(T d = 2; d * d <= x; d++)
        if(x % d == 0)
            return false;
    return true;
}

int main()
{
    static bitset<MAX> is_composite;
    vector<uint64_t> primes;
    for(uint64_t i = 2; i < MAX; i += 2)
    {
        if(not is_composite[i])
            primes.push_back(i);
        for(uint64_t x = i*i; x < MAX; x += i)
            is_composite[x] = true;
        if(i == 2) i--;
    }
    uint32_t j;
    cin >> j;
    uint64_t last = 0;
    for(uint32_t i = 0; i < primes.size() and j; i += 2)
    {
        uint64_t x = primes[i] * POW10[ndigits<uint64_t, 10>(primes[i+1])]
                     + primes[i+1];
        if((x < MAX and not is_composite[x]) or is_prime_sqrt(x))
        {
            last = x;
            j--;
        }
    }
    cout << last;
}
