#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

template<typename T>
struct mod_multiplies;

template<>
struct mod_multiplies<uint32_t> : multiplies<uint32_t>
{
    uint32_t m;
    mod_multiplies(uint32_t _m) : m(_m) {}
    uint32_t operator()(uint32_t a, uint32_t b) const
    {
        return ((uint64_t)a * b) % m;
    }
};

template<typename T>
T mod_mul(T a, T b, T m)
{
    mod_multiplies<T> M(m);
    return M(a, b);
}

template<typename T>
T discrete_logarithm(T a, T b, T m)
{
    a %= m; b %= m;
    if(b == 1)
        return 0;

    T cnt = 0, t = 1;
    for(T g = __gcd(a, m); g != 1; g = __gcd(a, m))
    {
        if(b % g) return numeric_limits<T>::max();
        m /= g; b /= g;
        t = mod_mul(t, a / g, m);
        ++cnt;
        if(b == t) return cnt;
    }

    a %= m;

    T k = ceil(sqrt(m));

    unordered_map<T, T> rhs; rhs.reserve(3 * k);
    T q = b;
    for(T j = 0; j < k; j++, q = mod_mul(q, a, m))
        rhs[q] = j;

    T w = power(a, k, mod_multiplies<T>(m));
    T p = mod_mul(w, t, m);
    for(T i = 1; i <= k; i++, p = mod_mul(p, w, m))
        if(rhs.count(p))
            return i * k - rhs[p] + cnt;

    return numeric_limits<T>::max();
}

int main()
{
    uint32_t a, b, m;
    while(cin >> a >> m >> b and m)
    {
        auto x = discrete_logarithm(a, b, m);
        if(x == -1u)
            cout << "No Solution" << endl;
        else
            cout << x << endl;
    }
}