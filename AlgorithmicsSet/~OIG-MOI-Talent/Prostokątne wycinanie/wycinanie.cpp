#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int uint64_t;

template<char P>
uint64_t sigma(uint64_t n)
{
    uint64_t r = 0;
    for(uint64_t i = 1; i <= n; i++)
        r += pow(n, P);
    return r;
}

template<>
uint64_t sigma<1>(uint64_t n)
{
    return n * (n + 1) / 2;
}
template<>
uint64_t sigma<2>(uint64_t n)
{
    return (2*n*n*n + 3*n*n + n) / 6;
}

uint64_t kappa(uint64_t n)
{
    return sigma<1>(n) * (n + 1) - sigma<2>(n);
}

int main()
{
    uint64_t w, h;
    cin >> w >> h;
    cout << kappa(w) * kappa(h);
}
