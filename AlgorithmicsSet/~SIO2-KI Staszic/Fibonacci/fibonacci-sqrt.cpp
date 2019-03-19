#include <bits/stdc++.h>

using namespace std;

const uint32_t MOD = 123456789;

uint32_t Fibb(uint32_t n)
{
    uint32_t a = 0, b = 1;
    for(uint32_t i = 0; i < n; i++)
        tie(a, b) = make_pair(b, (a + b) % MOD);
    return a;
}

uint32_t Fib(uint32_t n)
{
    if(n == 0) return 0;

    const uint32_t k = floor(sqrt(n));
    uint32_t j0 = 0, j1 = 1;
    for(uint32_t i = 0; i < k - 1; i++)
        tie(j0, j1) = make_pair(j1, (j0 + j1) % MOD);

    uint64_t a = 0, b = 1;
    uint32_t i = 0;
    while(i + k <= n)
    {
        tie(a, b) = make_pair(
          (b*j1 + a*j0) % MOD,
          ((a+b)*j1 + b*j0) % MOD
        );
        i += k;
    }
    while(i < n)
    {
        tie(a, b) = make_pair(b, (a + b) % MOD);
        i++;
    }
    return a;
}

int main()
{
    uint32_t n;
    cin >> n;
    cout << Fib(n);
}
