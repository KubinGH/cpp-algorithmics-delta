#include <bits/stdc++.h>
#include <ext/numeric>
#include <ktl/math/mod_multiplies.cpp>

using namespace std;
using __gnu_cxx::power;

bool miller_rabin_primality_witness(uint64_t n, uint64_t d, size_t r, uint64_t a)
{
    mod_multiplies<uint64_t> Z(n);

    auto x = power(a, d, Z);

    if(x == 1 or x == n - 1)
        return true;

    for(size_t i = 1; i < r; i++)
    {
        x = Z(x, x);
        if(x == n - 1)
            return true;
    }

    return false;
}

const size_t TRIES = 32;

bool is_prime(uint64_t n)
{
    if(n <= 1) return false;
    else if(n <= 3) return true;
    else if(n % 2 == 0) return false;

    size_t r = __builtin_ctz(n - 1);
    uint64_t d = (n - 1) >> r;

    mt19937_64 gen((size_t)make_unique<char>().get());
    uniform_int_distribution<uint64_t> dis(2, n - 2);
    for(size_t t = 0; t < TRIES; t++)
    {
        auto a = dis(gen);
        if(not miller_rabin_primality_witness(n, d, r, a))
            return false;
    }

    return true;
}

int main()
{
    size_t n;
    cin >> n;
    while(n --> 0)
    {
        uint64_t a;
        cin >> a;
        cout << (is_prime(a) ? "TAK" : "NIE") << '\n';
    }
}
