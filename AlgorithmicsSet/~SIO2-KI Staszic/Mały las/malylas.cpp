#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500001;

int main()
{
    uint32_t n;
    cin >> n;
    static array<bool, MAX> P;
    P.fill(true); P[0] = P[1] = false;
    for(uint32_t i = 4; i <= n; i += 2)
        P[i] = false;
    vector<uint32_t> primes;
    primes.push_back(2);
    for(uint32_t i = 3; i <= n; i += 2)
    {
        if(not P[i])
            continue;
        for(uint32_t x = i*i; x <= n; x += i)
            P[x] = false;
        primes.push_back(i);
    }
    uint32_t result = n + 2;
    static array<bool, MAX> U;
    for(uint32_t i = 1; i <= n; i++)
    {
        uint32_t ac = 0, c = n - 1;
        for(uint32_t p : primes)
        {
            if(__gcd(i, p) == 1) for(uint32_t x = p; x <= n; x += p)
            {
                if(__gcd(i, x) == 1 and not U[x])
                {
                    result++;
                    ac++;
                    cout << "(" << i << ", " << x << ")" << endl;
                    U[x] = true;
                }
            }
            else
                c -= n / p;
        }
        cout << ac << " " << c << endl;
        fill(U.begin(), U.begin() + n + 1, false);
    }
    cout << result;
}
