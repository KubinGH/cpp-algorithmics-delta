#include <bits/stdc++.h>

using namespace std;

const uint MAX = 1 << 20;

int main()
{
    vector<uint> totient(MAX);
    vector<bool> prime(MAX, true), prime_power(MAX);

    for(uint p = 2; p < MAX; p++)
    {
        if(prime[p])
        {
            for(uint64_t q = p; q < MAX; q *= p)
            {
                prime_power[q] = true;
                totient[q] = q/p * (p - 1);
            }
            for(uint x = 2*p; x < MAX; x += p)
            {
                if(not prime_power[x])
                {
                    uint q = x, t = 1;
                    while(q % p == 0) q /= p, t *= p;
                    totient[x] = totient[q] * totient[t];
                }
                prime[x] = false;
            }
        }
    }

    uint T;
    cin >> T;
    while(T --> 0)
    {
        uint n, m;
        cin >> n >> m;

        uint64_t r = 0;
        for(uint c = 1; c <= m; c++)
            r += uint64_t(n/c) * totient[c];
        r *= 2; r += n;

        cout << r << endl;
    }
}
