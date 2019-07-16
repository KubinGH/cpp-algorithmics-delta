#include "ktl/math/mod_multiplies.cpp"
#include "ktl/math/egcd.cpp"
#include "ktl/math/primality.cpp"
#include "ktl/util/chronohelper.cpp"
#include <ext/numeric>
#include <bits/stdc++.h>

using __gnu_cxx::power;
using namespace std;

uint64_t mod_inv_fermat(uint64_t a, uint64_t n)
{
    return power(a, n - 2, mod_multiplies<uint64_t>(n));
}

void xgcd(long *result, long a, long b){
    long aa[2]={1,0}, bb[2]={0,1}, q;
    while(1) {
        q = a / b; a = a % b;
        aa[0] = aa[0] - q*aa[1];  bb[0] = bb[0] - q*bb[1];
        if (a == 0) {
            result[0] = b; result[1] = aa[1]; result[2] = bb[1];
            return;
        };
        q = b / a; b = b % a;
        aa[1] = aa[1] - q*aa[0];  bb[1] = bb[1] - q*bb[0];
        if (b == 0) {
            result[0] = a; result[1] = aa[0]; result[2] = bb[0];
            return;
        };
    };
}

uint64_t mod_inv_egcd(uint64_t a, uint64_t n)
{
    long result[3];
    xgcd(result, a, n);
    auto v = result[1] % (int64_t)n;
    return v < 0 ? v + n : v;
}

int main()
{

    mt19937_64 gen(1337);
    auto randint = [&](uint64_t a, uint64_t b) {
        return uniform_int_distribution<uint64_t>{a, b}(gen);
    };

    vector<pair<uint64_t, uint64_t>> cases(1 << 15);

    for(auto& c : cases)
    {
        uint64_t a, n;
        do {
            n = randint(0, 1ull << 62);
        } while(not is_prime(n));
        a = randint(0, n - 1);
        c = {a, n};
    }

    auto t1 = nanos();
    for(const auto& c : cases)
        auto r = mod_inv_fermat(c.first, c.second);
    auto t2 = nanos();
    for(const auto& c : cases)
        auto r = mod_inv_egcd(c.first, c.second);
    auto t3 = nanos();

    auto d1 = (t2 - t1), d2 = (t3 - t2);
    cout << "Fermat: " << d1 << "ns" << endl;
    cout << "Euclidean: " << d2 << "ns" << endl;

    cout << "===\nRatio: " << fixed << setprecision(2) << (double)d1/d2 << endl;
}
