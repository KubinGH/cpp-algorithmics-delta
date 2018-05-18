#include <bits/stdc++.h>

using namespace std;

const size_t SIEVE_MAX = 1e6+1;

bitset<SIEVE_MAX> is_prime;
vector<uint32_t> primes;
bool done[SIEVE_MAX], cache[SIEVE_MAX];

bool R(uint32_t x)
{
    if(done[x])
        ;
    else if(x <= 1 or is_prime[x])
        cache[x] = false;
    else if(is_prime[x])
        cache[x] = true;
    else
    {
        bool any = false;
        uint32_t bx = x;
        for(uint32_t p : primes)
        {
            if(p > bx)
                break;
            if(x % p == 0)
            {
                if(not R(x - p))
                {
                    any = true;
                    break;
                }
                while(bx % p == 0)
                    bx /= p;
            }
        }
        cache[x] = any;
    }
    done[x] = true;
    return cache[x];
}

bool RR(uint32_t x)
{
    return x == 4 or not (x%2 or __builtin_popcount(x) == 1);
}

int main()
{
    is_prime.set();
    is_prime[0] = is_prime[1] = false;
    primes.push_back(2);
    for(uint32_t x = 4; x < SIEVE_MAX; x += 2)
        is_prime[x] = false;
    for(uint32_t i = 3; i < SIEVE_MAX; i += 2)
    {
        if(not is_prime[i])
            continue;
        primes.push_back(i);
        if(i < sqrt(SIEVE_MAX) + 32)
            for(uint32_t x = i*i; x < SIEVE_MAX; x += i)
                is_prime[x] = false;
    }
    for(uint32_t x = 1; x <= 1e6; x++)
    {
        cout << x << ": " << R(x) << " " << RR(x) << "\n";
        assert(R(x) == RR(x));
    }
}
