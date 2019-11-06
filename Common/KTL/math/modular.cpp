// Modular integers - mints.
// Useful when writing complicated code involving modular arithmetic, e.g. combinatorics DP or for adapting algorithms such as FFT or Gaussian Elimination.
// Should work pretty well with a few assumptions:
// * division is only done for coprime
// * global modulos are up to 4 times slower than normal
// * `-O3` should optimize the templated modulo enough to have almost no loss compared to hand-written statements. Worse optimizations may be ~2 times slower.
// `mint_global_mod` sets and returns the global modulo. Use 0 to not change anything. Moduli are set per-type.
// `UseFermat` - use Fermat's Little Theorem for computing the modular inverse. Obviously, primality is required. Otherwise Extended GCD will be used.
// `DoubleWordMultiply` - do multiplication on variables twice the size of T. Refers to `mod_multiplies.cpp`.
// Note: when facing operator-related compiler errors, cast everything to the mint type.
// _KTL_DEBUG enables coprimality checks when trying to compute the modular inverse.

// Last revision: April 2019

#pragma once

#include <ext/numeric>
#include <functional>
#include <iostream>
#include <cstdint>
#include <limits>
#include "mod_multiplies.cpp"
#include "egcd.cpp"

#include "../ktl_debug_mode.cpp"
#ifdef _KTL_DEBUG
#include <algorithm>
using std::__gcd;
#endif

using std::numeric_limits;
using std::is_same; using std::enable_if;
using std::is_integral; using std::is_unsigned;
using std::__lg;
using std::ostream; using std::istream;
using __gnu_cxx::power;

template<typename T>
T mint_global_mod(T m)
{
    static T mod = 0;
    if(m != 0)
        mod = m;
    return mod;
}

template<
    typename T, T _Mod, bool UseFermat = true,
    bool DoubleWordMultiply = (_Mod == 0) or (numeric_limits<T>::digits < 2 * (__lg(_Mod) + 2))
>
struct mint
{
    static_assert(is_unsigned<T>::value and is_integral<T>::value, "Invalid value type");

    template<bool enabled = _Mod != 0>
    static constexpr typename enable_if<    enabled, T>::type Mod() { return _Mod; }
    template<bool enabled = _Mod != 0>
    static constexpr typename enable_if<not enabled, T>::type Mod() { return mint_global_mod<T>(0); }

    T value;

    mint() : value(0) {}

    template<typename Ti>
    mint(Ti raw_value)
    {
        raw_value %= Ti(Mod());
        if(raw_value < 0)
            raw_value += Ti(Mod());
        value = raw_value;
    }

    mint operator- () const { return Mod() - value; }
    mint operator+ (const mint& other) const { return (value + other.value) % Mod(); }
    mint operator- (const mint& other) const { return *this + -other; }

    #define EXPLICIT_CONVERSION(__T) \
        explicit operator __T() const { return value; }
    EXPLICIT_CONVERSION(std::int16_t)
    EXPLICIT_CONVERSION(std::uint16_t)
    EXPLICIT_CONVERSION(std::int32_t)
    EXPLICIT_CONVERSION(std::uint32_t)
    EXPLICIT_CONVERSION(std::int64_t)
    EXPLICIT_CONVERSION(std::uint64_t)
    #undef EXPLICIT_CONVERSION

    #define PARAM_ENABLE(__VAL, __NAME, __POST) \
    template<bool enabled = __VAL> \
    mint __NAME (typename enable_if<enabled, const mint&>::type other) __POST
    #define PARAM_DISABLE(__VAL, __NAME, __POST) \
    template<bool enabled = __VAL> \
    mint __NAME (typename enable_if<not enabled, const mint&>::type other) __POST

    PARAM_ENABLE (DoubleWordMultiply, operator*, const) { return mod_mul(value, other.value, Mod()); }
    PARAM_DISABLE(DoubleWordMultiply, operator*, const) { return (value * other.value) % Mod(); }

    PARAM_ENABLE (UseFermat, operator/, const) { KTL_DEBUG_ASSERT(__gcd(other.value, Mod()) == 1); return *this * power(other, Mod() - 2); }
    PARAM_DISABLE(UseFermat, operator/, const) { KTL_DEBUG_ASSERT(__gcd(other.value, Mod()) == 1); return *this * mint(egcd(other.value, Mod()).x); }

    #undef PARAM_ENABLE
    #undef PARAM_DISABLE

    #define INPLACE_ARITHMETIC(__IP, __OP) \
        mint& operator __IP (const mint& o) { return *this = *this __OP o; }
    INPLACE_ARITHMETIC(+=, +)
    INPLACE_ARITHMETIC(-=, -)
    INPLACE_ARITHMETIC(*=, *)
    INPLACE_ARITHMETIC(/=, /)
    #undef INPLACE_ARITHMETIC

    mint& operator++ () { ++value; if(value == Mod()) value = 0; return *this; }
    mint& operator-- () { if(value == 0) value = Mod; --value; return *this; }
    mint operator++ (int) { auto c = *this; ++*this; return c; }
    mint operator-- (int) { auto c = *this; --*this; return c; }

    #define COMPARISON(__OP) bool operator __OP (const mint& other) const { return this->value __OP other.value; }
    COMPARISON(<)
    COMPARISON(<=)
    COMPARISON(>)
    COMPARISON(>=)
    COMPARISON(==)
    COMPARISON(!=)
    #undef COMPARISON

    bool operator! () const { return not value; }
};

#define MINT_PARAM typename T, T _Mod, bool UseFermat, bool DoubleWordMultiply
#define MINT_DECL mint<T, _Mod, UseFermat, DoubleWordMultiply>
#define MAKE_BIDIRECTIONAL(__OP) \
template<MINT_PARAM, typename Ti> \
typename enable_if<not is_same<MINT_DECL, Ti>::value, MINT_DECL>::type \
operator __OP (const Ti& a, const MINT_DECL& b) { return decltype(b)(T(a)) __OP b; }
MAKE_BIDIRECTIONAL(+)
MAKE_BIDIRECTIONAL(-)
MAKE_BIDIRECTIONAL(*)
MAKE_BIDIRECTIONAL(/)
#undef MAKE_BIDIRECTIONAL

template<MINT_PARAM>
istream& operator>> (istream& in, MINT_DECL& m) { T v; in >> v; m = MINT_DECL(v); return in; }
template<MINT_PARAM>
ostream& operator<< (ostream& out, const MINT_DECL& m) { return out << m.value; }

#undef MINT_PARAM
#undef MINT_DECL
