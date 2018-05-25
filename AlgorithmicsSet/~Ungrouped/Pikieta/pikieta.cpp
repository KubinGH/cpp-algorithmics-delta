#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 50000, MAX_SQRT = 256;
const uint64_t MOD = 12345678;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    vector<uint32_t> primes;
    static bitset<MAX_SQRT> is_prime; is_prime.set();
    is_prime[0] = is_prime[1] = false;
    for(uint32_t i = 4; i < MAX_SQRT; i += 2)
        is_prime[i] = false;
    primes.push_back(2);
    for(uint32_t i = 3; i < MAX_SQRT; i += 2)
    {
        if(not is_prime[i])
            break;
        for(uint32_t x = i*i; x < MAX_SQRT; x += i)
            is_prime[x] = false;
        primes.push_back(i);
    }
    uint32_t n;
    cin >> n;
    static uint32_t fact_count[MAX+1];
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a;
        cin >> a;
        for(uint32_t p : primes)
        {
            if(a == 1)
                break;
            uint32_t c = 0;
            while(a % p == 0)
            {
                c++;
                a /= p;
            }
            fact_count[p] = max(fact_count[p], c);
        }
        if(a != 1)
            fact_count[a] = max(fact_count[a], 1u);
    }
    uint64_t r = 1;
    for(uint32_t i = 0; i <= MAX; i++)
        r *= uint64_t(fact_count[i] + 1), r %= MOD;
    cout << (r + MOD - n) % MOD;
}
