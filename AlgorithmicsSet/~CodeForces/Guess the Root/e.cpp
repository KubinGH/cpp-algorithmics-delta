#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

#ifdef _KTL_DEBUG
#include <cassert>
#define KTL_DEBUG_ASSERT(__EXPR) assert(__EXPR)
#else
#define KTL_DEBUG_ASSERT(_)
#endif

using namespace std;

template<typename T>
bool gauss_is_zero(const T& v)
    { return v == T(0); }
template<>
bool gauss_is_zero<double>(const double& v)
    { return abs(v) < 1e-5; }
template<>
bool gauss_is_zero<long double>(const long double& v)
    { return abs(v) < 1e-10; }

template<typename T>
bool gauss_compare_sel(const T& a, const T& b)
    { return a < b; }
template<>
bool gauss_compare_sel<double>(const double& a, const double& b)
    { return abs(a) < abs(b); }
template<>
bool gauss_compare_sel<long double>(const long double& a, const long double& b)
    { return abs(a) < abs(b); }

template<typename T>
vector<size_t> gaussian_elimination(vector<vector<T>>& a, size_t& swap_count)
{
    const size_t n = a.size();
    const size_t m = a[0].size() - 1;

    KTL_DEBUG_ASSERT(all_of(a.begin(), a.end(), [&](const vector<T>& v) { return a[0].size() == v.size(); }));

    vector<size_t> where (m, SIZE_MAX);
    for(size_t col = 0, row = 0; col < m and row < n; col++)
    {
        size_t select = row;
        for(size_t i = row; i < n; i++)
            if(gauss_compare_sel(a[select][col], a[i][col]))
                select = i;

        if(gauss_is_zero(a[select][col]))
            continue;

        a[row].swap(a[select]);
        if(row != select)
            swap_count++;
        where[col] = row;

        for(size_t i=0; i<n; ++i)
        {
            if(i != row)
            {
                T c = a[i][col] / a[row][col];
                for(size_t j = col; j <= m; j++)
                    a[i][j] -= a[row][j] * c;
            }
        }
        row++;
    }
    return where;
}

template<typename T>
vector<size_t> gaussian_elimination(vector<vector<T>>& a)
{
    size_t _ = 0;
    return gaussian_elimination(a, _);
}

enum equation_system_status { None, Unique, Infinite };

template<typename T>
pair<equation_system_status, vector<T>> solve_system_of_linear_equations(vector<vector<T>> eq)
{
    const size_t n = eq.size();
    const size_t m = eq[0].size() - 1;

    auto where = gaussian_elimination(eq);

    vector<T> solution(m, 0);

    for(size_t i = 0; i < m; i++)
        if(where[i] != SIZE_MAX)
            solution[i] = eq[where[i]][m] / eq[where[i]][i];

    for(size_t i = 0; i < n; i++)
    {
        T sum = 0;
        for(size_t j = 0; j < m; j++)
            sum += solution[j] * eq[i][j];
        if(not gauss_is_zero(sum - eq[i][m]))
            return {None, {}};
    }

    for(size_t i = 0; i < m; i++)
        if(where[i] == SIZE_MAX)
            return {Infinite, solution};

    return {Unique, solution};
}

template<typename T>
T determinant(vector<vector<T>> a)
{
    KTL_DEBUG_ASSERT(a.size() == a[0].size());

    size_t swap_count = 0;
    auto where = gaussian_elimination(a, &swap_count);

    T result = 1;
    for(size_t i = 0; i < a.size(); i++)
        result *= a[i][i];

    return swap_count % 2 ? -result : result;
}

template<typename T>
struct mod_multiplies;

template<>
struct mod_multiplies<uint64_t> : multiplies<uint64_t>
{
    uint64_t m;
    mod_multiplies(uint64_t _m) : m(_m) { KTL_DEBUG_ASSERT(m > 0); }
    uint64_t operator() (uint64_t a, uint64_t b) const
    {
        if(a >= m) a %= m;
        if(b >= m) b %= m;
#ifndef __x86_64__
        uint64_t c = (long double)(a) * b / m;
        int64_t r = a * b - c * m;
        return r < 0 ? r%(int64_t)m + m : r%(int64_t)m;
#else
        __extension__ unsigned __int128 c = a;
        c *= b;
        c %= m;
        return c;
#endif
    }
};

template<>
struct mod_multiplies<uint32_t> : multiplies<uint32_t>
{
    uint32_t m;
    mod_multiplies(uint32_t _m) : m(_m) { KTL_DEBUG_ASSERT(m > 0); }
    uint32_t operator() (uint32_t a, uint32_t b) const
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
        raw_value %= Mod();
        if(raw_value < 0)
            raw_value += Mod();
        value = raw_value;
    }

    mint operator- () const { return Mod() - value; }
    mint operator+ (const mint& other) const { return (value + other.value) % Mod(); }
    mint operator- (const mint& other) const { return *this + -other; }

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

    #define COMPARISON(__OP) bool operator __OP (const mint& other) const { return this->value __OP other.value; }
    COMPARISON(<)
    COMPARISON(<=)
    COMPARISON(>)
    COMPARISON(>=)
    COMPARISON(==)
    COMPARISON(!=)
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

const uint32_t MOD = 1e6 + 3;
const size_t Q = 50, K = 10;

int main()
{
    using Z = mint<uint32_t, MOD>;

    vector<vector<Z>> equations(Q, vector<Z>(K+2));
    for(size_t i = 0; i < Q; i++)
    {
        for(size_t j = 0; j <= K; j++)
            equations[i][j] = power(Z(i), j);
        cout << "? " << i << endl;
        cin >> equations[i][K+1];
    }

    auto A = solve_system_of_linear_equations(equations).second;

    for(size_t x = 0; x < MOD; x++)
    {
        Z y = 0, c = 1;
        for(size_t i = 0; i <= K; i++)
        {
            y += A[i] * c;
            c *= x;
        }
        if(y == 0)
        {
            cout << "! " << x << endl;
            return 0;
        }
    }
    cout << "! " << -1 << endl;
}