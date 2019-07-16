#include <bits/stdc++.h>
#include "ktl/math/mod_multiplies.cpp"
#include "ktl/math/primality.cpp"
#include "ktl/util/debug_macros.cpp"

using namespace std;

template<typename T>
T pollard_rho_get_factor(T n)
{
    if(is_prime(n))
        return n;

    size_t it = 0;
    for(T c = 3; true; c++)
    {
        cdbg << note(it) << endl;
        auto f = [c, n](T x) {
            return (mod_mul(x, x, n) + c) % n;
        };
        T x = 2, y = 2, d = 1;
        size_t steps = 0;
        while(d == 1)
        {
            x = f(x);
            y = f(f(y));
            d = __gcd(x>y ? x-y : y-x, n);
            steps++;
        }
        cdbg << note(steps) << endl;
        if(d != n)
            return d;
    }
    return 1;
}

int main()
{
    unsigned long n;
    //cin >> n;
    mt19937 gen(random_device{}());
    for(size_t i = 0; i < 1024; i++)
    {
        n = uniform_int_distribution<unsigned long>{1, 1l << 50}(gen);
        cdbg << note(n) << endl;
        auto p = pollard_rho_get_factor(n);
        cdbg << "p = " << p << endl;
    }
}
