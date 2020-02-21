#include <algorithm>
#include <iostream>
#include <bitset>
#include <random>
#include <vector>
#include <stack>
#include <map>

// Biblioteka KTL jest mojego autorstwa. Zaznaczam,
// ze jest ogolnodostepna w Internecie.


// -*- ktl/ktl_debug_mode.cpp -*-

#ifdef _KTL_DEBUG
#include <cassert>
#define KTL_DEBUG_ASSERT(__EXPR) assert(__EXPR)
#else
#define KTL_DEBUG_ASSERT(_)
#endif

// -$- ktl/ktl_debug_mode.cpp -$-

// -*- ktl/math/mod_multiplies.cpp -*-

#include <functional>
#include <cstdint>

using std::multiplies;
using std::uint64_t; using std::int64_t;
using std::uint32_t;

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

// -$- ktl/math/mod_multiplies.cpp -$-

// -*- ktl/math/egcd.cpp -*-

#include <cstdint>

using std::int64_t;

struct egcd_res { int64_t d, x, y; };
egcd_res egcd(int64_t a, int64_t b)
{
    if(a == 0)
        return {b, 0, 1};
    auto r = egcd(b % a, a);
    return {r.d, r.y - (b/a)*r.x, r.x};
}

// -$- ktl/math/egcd.cpp -$-

// -*- ktl/math/modular.cpp -*-

#include <ext/numeric>
#include <functional>
#include <iostream>
#include <cstdint>
#include <limits>

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

// -$- ktl/math/modular.cpp -$-


// -*- ktl/math/gaussian_elimination.cpp -*-

#include <cmath>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <utility>
#ifdef _KTL_DEBUG
#include <algorithm>
using std::all_of;
#endif

using std::abs;
using std::vector; using std::pair;
using std::size_t;

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

        for(size_t i = 0; i < n; i++)
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
    auto where = gaussian_elimination(a, swap_count);

    T result = 1;
    for(size_t i = 0; i < a.size(); i++)
        result *= a[i][i];

    return swap_count % 2 ? -result : result;
}

// -$- ktl/math/gaussian_elimination.cpp -$-


using namespace std;

const uint MOD = 1e9 + 7;

using mymint = mint<uint, MOD>;
using graph_t = vector<vector<size_t>>;

vector<vector<size_t>> get_components(const graph_t& graph)
{
    vector<bool> vis(graph.size());
    vector<size_t> run;
    function<void(size_t)> dfs = [&](size_t u) {
        run.push_back(u);
        vis[u] = true;
        for(auto v : graph[u])
            if(not vis[v])
                dfs(v);
    };
    vector<vector<size_t>> result;
    for(size_t u = 0; u < graph.size(); u++)
    {
        if(vis[u]) continue;
        dfs(u);
        result.push_back(run);
        run.clear();
    }
    return result;
}

bool randomness[64] = {
    0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1,
    1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1,
    1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0,
    0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0
};
struct disjoint_set
{
    struct save { size_t u, v, up, vsm, vom; };
    vector<size_t> parent, selfmask, outmask;
    vector<save> saves;

    disjoint_set(size_t n) : parent(n), selfmask(n), outmask(n)
    {
        iota(parent.begin(), parent.end(), 0);
        for(size_t i = 0; i < n; i++)
            selfmask[i] = 1 << i;
        saves.reserve(n);
    }
    size_t sets() const
    {
        return parent.size() - saves.size();
    }
    bool conn(size_t u, size_t v) const
    {
        return (outmask[u] & selfmask[v]) or (outmask[v] & selfmask[u]);
    }
    size_t find(size_t u) const
    {
        return u == parent[u] ? u : find(parent[u]);
    }
    bool unite(size_t u, size_t v)
    {
        static size_t no = 0;
        if((u = find(u)) != (v = find(v)))
        {
            if(randomness[no = (no+1)&63]) swap(u, v);
            saves.push_back({u, v, parent[u], selfmask[v], outmask[v]});
            parent[u] = v;
            selfmask[v] |= selfmask[u];
            outmask[v] |= outmask[u];
            return true;
        }
        else
            return false;
    }
    void rollback()
    {
        const auto& s = saves.back();
        parent[s.u] = s.up;
        selfmask[s.v] = s.vsm;
        outmask[s.v] = s.vom;
        saves.pop_back();
    }
};

namespace cycles
{

    map<uint, mymint> solve(graph_t graph, vector<uint> K)
    {
        vector<size_t> S;
        for(auto cc : get_components(graph))
            S.push_back(cc.size());

        sort(S.begin(), S.end());
        vector<pair<size_t, uint>> C = {{0, 0}};

        for(auto s : S)
        {
            if(C.back().first != s)
                C.emplace_back(s, 0);
            C.back().second++;
        }
        C.erase(C.begin());

        map<uint, mymint> answer;
        sort(K.begin(), K.end());
        for(auto k : K)
        {
            mymint result = 1;
            mymint l = k - 1;
            for(auto [s, c] : C)
                result *= power(power(l, s) + (s%2 ? -l : l), c);
            answer[k] = result;
        }

        return answer;
    }
}

namespace general
{
    const size_t MAX = 31;

    vector<bool> get_independent_sets(const graph_t& graph)
    {
        const size_t n = graph.size();
        array<size_t, MAX> nin;
        for(size_t u = 0; u < n; u++)
        {
            nin[u] = (1 << n) - 1;
            for(size_t v : graph[u])
                nin[u] &= ~(1 << v);
        }

        vector<bool> ind(1 << n, true);
        for(size_t mask = 1; mask < (1u << n); mask++)
        {
            for(size_t u = 0; u < n; u++)
              if((mask & (1 << u)) and (nin[u] & mask) != mask)
            {
                ind[mask] = false;
                break;
            }
        }

        return ind;
    }

    vector<mymint> k_colorings(const graph_t& graph)
    {
        const size_t n = graph.size();
        vector<mymint> A(1 << n), B = A;
        auto ind = get_independent_sets(graph);
        B[0] = 1;
        vector<mymint> result(n+1);
        for(size_t k = 1; k <= n; k++)
        {
            A[0] = 1;
            for(size_t mask = 1; mask < (1u << n); mask++)
            {
                A[mask] = 0;
                size_t sub = 0;
                do {
                    if(ind[sub])
                        A[mask] += B[mask ^ sub];
                } while((sub = (sub-1) & mask));
            }
            result[k] = A.back();
            swap(A, B);
        }
        return result;
    }

    void deletion_contraction_coloring(
        const vector<pair<size_t, size_t>>& edges,
        disjoint_set& dset, vector<mymint>& out, size_t i = 0, int sign = 1
    )
    {
        if(dset.sets() == 1)
            out[1] += sign;
        else if(i < edges.size())
        {
            auto [s, t] = edges[i];
            s = dset.find(s); t = dset.find(t);

            if(s != t and dset.conn(s, t))
            {
                auto ms = dset.outmask[s], mt = dset.outmask[t];
                dset.outmask[s] &= ~dset.selfmask[t];
                dset.outmask[t] &= ~dset.selfmask[s];
                deletion_contraction_coloring(edges, dset, out, i + 1, sign);
                dset.outmask[s] = ms;
                dset.outmask[t] = mt;

                dset.unite(s, t);
                deletion_contraction_coloring(edges, dset, out, i + 1, -sign);
                dset.rollback();
            }
            else
                deletion_contraction_coloring(edges, dset, out, i + 1, sign);
        }
        else
            out[dset.sets()] += sign;
    }

    vector<mymint> get_chromatic_polynomial_conn(const graph_t& graph)
    {
        const size_t n = graph.size();
        size_t m = 0;
        for(size_t u = 0; u < n; u++)
            m += graph[u].size();
        m /= 2;
        if((double)m/n > log2(3))
        {
            vector<vector<mymint>> eq(n+1, vector<mymint>(n+2));
            vector<mymint> Y = k_colorings(graph);
            for(size_t x = 0; x <= n; x++)
            {
                eq[x][0] = 1;
                for(size_t i = 1; i <= n; i++)
                    eq[x][i] = eq[x][i-1] * x;
                eq[x].back() = Y[x];
            }
            return solve_system_of_linear_equations(eq).second;
        }
        else
        {
            vector<pair<size_t, size_t>> edges;
            disjoint_set dset(n);
            for(size_t u = 0; u < n; u++)
                for(auto v : graph[u])
            {
                if(u < v)
                    edges.emplace_back(u, v);
                dset.outmask[u] |= 1 << v;
            }
            static mt19937 gen(42);
            shuffle(edges.begin(), edges.end(), gen);

            vector<mymint> coeff(n+1);
            deletion_contraction_coloring(edges, dset, coeff);
            return coeff;
        }
    }

    pair<vector<mymint>, uint> get_chromatic_polynomial(const graph_t& graph)
    {
        vector<mymint> P = {1};

        static mt19937 gen(1337);

        uint shift = 0;
        for(auto cc : get_components(graph))
        {
            shuffle(cc.begin(), cc.end(), gen);
            if(cc.size() == 1)
            {
                shift++;
                continue;
            }
            graph_t sub(cc.size());
            auto idx = [&](size_t u) {
                return find(cc.begin(), cc.end(), u) - cc.begin();
            };
            for(auto u : cc)
                for(auto v : graph[u])
                    sub[idx(u)].push_back(idx(v));

            auto Q = get_chromatic_polynomial_conn(sub);

            vector<mymint> R(P.size() + Q.size());
            for(size_t i = 0; i < P.size(); i++)
                for(size_t j = 0; j < Q.size(); j++)
                    R[i+j] += P[i] * Q[j];
            P = R;
        }

        return {P, shift};
    }

    map<uint, mymint> solve(graph_t graph, vector<uint> X)
    {
        auto [poly, shift] = get_chromatic_polynomial(graph);
        map<uint, mymint> answer;
        for(auto x : X)
        {
            mymint result = 0;
            for(size_t k = poly.size(); k --> 0; )
                result *= x, result += poly[k];

            result *= power(mymint(x), shift);
            answer[x] = result;
        }
        return answer;
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, q;
    cin >> n >> m >> q;

    graph_t graph(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<uint> queries(q);
    for(auto& x : queries)
        cin >> x;

    map<uint, mymint> answer;

    if(all_of(graph.begin(), graph.end(), [&](const vector<size_t>& vec) {
        return vec.size() == 2;
    }))
        answer = cycles::solve(graph, queries);
    else
        answer = general::solve(graph, queries);

    for(auto x : queries)
        cout << answer[x] << '\n';
}
