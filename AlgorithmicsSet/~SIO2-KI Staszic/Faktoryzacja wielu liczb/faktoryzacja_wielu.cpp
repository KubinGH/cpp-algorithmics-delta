#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000001;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    static bitset<MAX> P;
    P.set(); P[0] = P[1] = false;
    vector<uint32_t> primes;
    primes.push_back(2);
    for(uint32_t i = 4; i <= MAX; i += 2)
        P[i] = false;
    uint32_t mark = 0;
    for(uint32_t i = 3; i <= MAX; i += 2)
    {
        if(not P[i])
            continue;
        if(i < (1 << 15)) for(uint32_t x = i*i; x <= MAX; x += i)
            P[x] = false;
        primes.push_back(i);
        if(i > 1000 and mark == 0)
            mark = primes.size();
    }
    uint32_t t;
    cin >> t;
    for(uint32_t ti = 0; ti < t; ti++)
    {
        uint32_t n;
        cin >> n;
        for(uint32_t i = 0; i < mark; i++)
        {
            uint32_t p = primes[i];
            if(n == 1) break;
            while(n % p == 0)
                n /= p, cout << p << ' ';
        }
        if(binary_search(primes.begin(), primes.end(), n))
            cout << n;
        cout << '\n';
    }
}
