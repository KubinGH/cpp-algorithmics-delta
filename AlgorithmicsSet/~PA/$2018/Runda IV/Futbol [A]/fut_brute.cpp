#include <bits/stdc++.h>
#include <ext/numeric>
#include "message.h"
#include "futbol.h"

using namespace std;
using __gnu_cxx::power;

template<typename T>
struct modulo_multiplies
{
    T divisor;
    modulo_multiplies(T _divisor) : divisor(_divisor) {}
    T operator() (T a, T b) { return (a*b) % divisor; }
};
template<typename T>
T identity_element(modulo_multiplies<T>) { return T(1); }

int main()
{
    const uint32_t I = NumberOfNodes(), this_id = MyNodeId();
    if(this_id != 0) return 0;
    const uint64_t n = GetN(), k = GetK(), p = GetP();
    modulo_multiplies<uint64_t> M(p);
    uint64_t c = 1, r = 1;
    for(uint64_t i = 1; i <= k; i++)
    {
        c *= (n - i + 1); c *= power(i, p - 2, M);
        r = (r + c) % p;
    }
    cout << r;
}
