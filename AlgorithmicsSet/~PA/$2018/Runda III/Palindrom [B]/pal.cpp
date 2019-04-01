#include <bits/stdc++.h>
#include <ext/numeric>
#ifndef _WIN32
#define getchar getchar_unlocked
#endif // _WIN32

using namespace std;
using __gnu_cxx::power;

const uint32_t N = 1 << 25;

template<typename T, typename MonoidOperation>
struct chain_multiplies
{
    MonoidOperation M;
    T operator() (T a, T b) const { return M(a*b); }
};
template<typename T, typename MonoidOperation>
static T identity_element(chain_multiplies<T, MonoidOperation>) { return T(1); }

template<typename T, T Base, typename ModuloOperation>
struct buffer_hash
{
    T value, base_exp, base_pow, base_inverse;
    ModuloOperation M;
    chain_multiplies<T, ModuloOperation> MM;
    buffer_hash(T _base_exp)
        : value(0), base_exp(_base_exp)
    {
        base_inverse = power(Base, M.divisor - 2, MM);
        base_pow = power(Base, base_exp, MM);
    }
    buffer_hash& operator^= (T x) { value = M(value + x * base_pow); return *this; }
    buffer_hash& operator++ () { base_exp++; base_pow = M(base_pow*Base); return *this; }
    buffer_hash& operator-- () { base_exp--; base_pow = M(base_pow*base_inverse); return *this; }
    buffer_hash& operator/= (T e)
    {
        base_exp -= e;
        T v = power(base_inverse, e, MM);
        base_pow = M(base_pow * v);
        value = M(value * v);
        return *this;
    }
};

template<typename T, T Divisor>
struct const_modulus
{
    static constexpr T divisor = Divisor;
    T operator() (T x) const { return x % Divisor; }
};
template<typename T, uint32_t K>
struct mersenne_modulus
{
    static constexpr T P = (T(1) << K) - 1, divisor = P;
    T operator() (T x) const
    {
        x = (x >> K) + (x & P);
        x = (x >> K) + (x & P);
        return x == P ? 0 : x;
    }
};

int main()
{
    uint32_t n;
    scanf("%u ", &n);
    buffer_hash<uint64_t, 331, mersenne_modulus<uint64_t, 31>>
        H(0), Ht(n ? n-1 : N-1);
    buffer_hash<uint64_t, 127, const_modulus<uint64_t, uint64_t(1e9+33)>>
        G(0), Gt(n ? n-1 : N-1);
    char curr; uint32_t rn = 0;
    while(isalpha(curr = getchar()))
    {
        H ^= (curr-'a'+13); Ht ^= (curr-'a'+13);
        ++H; --Ht;
        G ^= (curr-'a'+2); Gt ^= (curr-'a'+2);
        ++G; --Gt;
        rn++;
    }
    if(n == 0)
        Ht /= N - rn, Gt /= N - rn;
    printf((H.value == Ht.value and G.value == Gt.value ? "TAK" : "NIE"));
}
