#include <bits/stdc++.h>
//#define FORCE_POLLARD_RHO
#include <ktl/math/primality.cpp>
#include <ktl/math/factorization.cpp>
#include <ktl/util/extio.cpp>
#include <ktl/util/chronohelper.cpp>

using namespace std;

int main()
{
    auto s1 = millis();
    cout << factorize_int((uint64_t)(1e8+213) * (uint64_t)(1e10+207)) << endl;
    cout << millis() - s1 << "ms" << endl;

    mt19937_64 gen(time(0));
    auto randint = [&](unsigned long a, unsigned long b) {
        return uniform_int_distribution<unsigned long>{a, b}(gen);
    };

    auto st = millis();
    size_t i = 0;
    while(millis() - st < 5000)
    {
        unsigned long n = randint(1, 1ul << 62);
        //cout << n << " = " << flush;
        auto f = factorize_int(n);
        //cout << f << endl;
        unsigned long m = 1;
        for(auto p : f)
        {
            m *= p;
            assert(is_prime(p));
        }
        assert(n == m);
        i++;
    }
    cout << fixed << setprecision(2) << (i / 3.) << " factorizations per second" << endl;
}
