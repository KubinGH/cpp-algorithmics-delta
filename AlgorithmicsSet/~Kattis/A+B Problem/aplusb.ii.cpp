// -*- ktl/ktl_debug_mode.cpp -*-

#ifdef _KTL_DEBUG
#include <cassert>
#define KTL_DEBUG_ASSERT(__EXPR) assert(__EXPR)
#else
#define KTL_DEBUG_ASSERT(_)
#endif

// -$- ktl/ktl_debug_mode.cpp -$-

// -*- ktl/math/fft.cpp -*-

#include <ext/numeric>
#include <functional>
#include <algorithm>
#include <complex>
#include <vector>
#include <cmath>

using std::vector; using std::complex;
using std::size_t;
using std::acos; using std::cos; using std::sin;
using std::function;
using std::swap;
using __gnu_cxx::power; using std::__lg;

namespace fft_base
{
    template<typename T>
    T bit_reverse(T x, size_t lim)
    {
        T y = 0;
        for(size_t i = 0; i < lim; i++, x >>= 1)
            if(x & 1)
                y |= (1 << (lim - i - 1));
        return y;
    }
    template<typename T, typename Ti>
    vector<T> convert(const vector<Ti>& iA, size_t req = 0)
    {
        vector<T> A(iA.begin(), iA.end());
        while(A.size() < req or (A.size() & (A.size()-1))) A.emplace_back(T(0));
        return A;
    }

    template<typename T>
    vector<T> call(vector<T> A, function<T(size_t, size_t)> w, size_t recalc = 0)
    {
        KTL_DEBUG_ASSERT((A.size() & (A.size() - 1)) == 0);

        const size_t n = A.size();

        for(size_t i = 0; i < n; i++)
        {
            size_t j = fft_base::bit_reverse(i, __lg(n));
            if(i < j)
                swap(A[i], A[j]);
        }

        for(size_t block = 2; block <= n; block *= 2)
        {
            T w_b = w(block, 1);
            for(size_t i = 0; i < n; i += block)
            {
                T t = 1;
                const size_t m = block / 2;
                for(size_t j = 0; j < m; j++)
                {
                    auto u = A[i+j], v = A[i+j+m] * t;
                    A[i+j]   = u + v;
                    A[i+j+m] = u - v;
                    if(recalc and j % recalc == 0)
                        t = w(block, j + 1);
                    else
                        t *= w_b;
                }
            }
        }

        return A;
    }
}

template<typename T, size_t Recalc = 16>
struct fft
{
    using C = complex<T>;
    static constexpr long double TAU = 2 * acos(-1.0L);
    static C root_of_unity(size_t k, size_t l) { return C(cos(TAU * l / k), sin(TAU * l / k)); }
    static C inverse_root_of_unity(size_t k, size_t l) { return T(1) / root_of_unity(k, l); }

    template<typename Ti>
    vector<C> operator() (const vector<Ti>& iA, size_t req = 0)
    {
        return fft_base::call(fft_base::convert<C>(iA, req), function<C(size_t, size_t)>(root_of_unity), Recalc);
    }
    template<typename Ti>
    vector<C> operator[] (const vector<Ti>& iY)
    {
        auto A = fft_base::call(fft_base::convert<C>(iY), function<C(size_t, size_t)>(inverse_root_of_unity), Recalc);
        for(size_t i = 0; i < A.size(); i++)
            A[i] /= A.size();
        return A;
    }
};

template<typename T, typename Tf, size_t Recalc = 16>
struct rfft
{
    fft<Tf, Recalc> transform;
    using C = typename fft<Tf>::C;

    vector<C> operator() (const vector<T>& A, size_t req = 0)
    {
        return transform(A, req);
    }

    vector<T> operator[] (const vector<C>& Y)
    {
        auto Ac = transform[Y];
        vector<T> A(Ac.size());
        for(size_t i = 0; i < Ac.size(); i++)
            A[i] = T(round(Ac[i].real()));
        return A;
    }
};

// -$- ktl/math/fft.cpp -$-


// -*- ktl/util/debug_macros.cpp -*-

#include <iostream>

using std::cerr;
using std::endl;
using std::ostream;

#ifndef KTL_DEBUG_MACROS
#if defined(XHOVA) && !defined(XHOVA_O)
#define KTL_DEBUG_MACROS
#endif
#endif

#define KTL_CDBG_COLOR_INIT    "\033[1;33m"
#define KTL_CDBG_COLOR_DEINIT  "\033[0m"

#define note(x) #x << " = " << (x)
#define short_pos "[" << __LINE__ << "]"
#define long_pos "[<" << __PRETTY_FUNCTION__ << ">::" << __LINE__ << "]"
#ifdef KTL_DEBUG_MACROS
#define debug(...)  cerr << KTL_CDBG_COLOR_INIT << __VA_ARGS__ << KTL_CDBG_COLOR_DEINIT
#define debugx(...) cerr << KTL_CDBG_COLOR_INIT << short_pos << ": " << __VA_ARGS__ << KTL_CDBG_COLOR_DEINIT << endl
#define debugX(...) cerr << KTL_CDBG_COLOR_INIT <<  long_pos << ": " << __VA_ARGS__ << KTL_CDBG_COLOR_DEINIT << endl
#else
#define debug(...) (void)0
#define debugx(...) (void)0
#define debugX(...) (void)0
#endif

struct cdbg_t
{
    template<typename T>
    cdbg_t& operator<< (const T& o)
    {
        (void)o;
#ifdef KTL_DEBUG_MACROS
        debug(o);
#endif
        return *this;
    }
    cdbg_t& operator<< (ostream& (*pf)(ostream&))
    {
        (void)pf;
#ifdef KTL_DEBUG_MACROS
        debug(pf);
#endif
        return *this;
    }
} cdbg;

// -$- ktl/util/debug_macros.cpp -$-

// -*- ktl/math/poly.cpp -*-

#include <vector>
#include <algorithm>

using std::vector;
using std::max;
using std::__lg;

template<typename T, typename Transform>
struct poly_multiplies
{
    Transform tr;
    using C = typename Transform::C;
    vector<T> operator() (const vector<T>& P, const vector<T>& Q)
    {
        if(P.empty() or Q.empty()) return {};
        size_t n = P.size() - 1, m = Q.size() - 1, r = n + m, r2 = 1 << __lg(2*(r + 1) - 1);
        auto U = tr(P, r2), V = tr(Q, r2);
        vector<C> W(r2);
        for(size_t i = 0; i < r2; i++)
            W[i] = U[i] * V[i];
        auto Rc = tr[W];
        vector<T> R(r + 1);
        for(size_t i = 0; i <= r; i++)
            R[i] = T(Rc[i]);
        while(not R.empty() and not R.back())
            R.pop_back();
        return R;
    }
};

template<typename V, typename Transform>
struct polynomial
{
    static poly_multiplies<V, Transform> mul;
    vector<V> P;

    polynomial() {}
    polynomial(size_t d) : P(d + 1) {}

    template<typename W>
    polynomial(const vector<W>& p)
    {
        P.resize(p.size());
        for(size_t i = 0; i < p.size(); i++)
            P[i] = V(p[i]);
    }
    polynomial (const vector<V>& p) : P(p) {};

    size_t degree() const { return P.size() - 1; }
    const V& at(size_t i) const { static V OUT = 0; return not P.empty() and i <= degree() ? P[i] : OUT; }
    V& operator[] (size_t i) { return P[i]; }
    const V& operator[] (size_t i) const { return P[i]; }

    polynomial operator+ (const polynomial& other) const
    {
        polynomial result(max(degree(), other.degree()));
        for(size_t i = 0; i <= degree(); i++)
            result[i] = at(i) + other.at(i);
        return result;
    }

    polynomial operator- () const
    {
        polynomial result = *this;
        for(size_t i = 0; i <= degree(); i++)
            result[i] = -result[i];
        return result;
    }

    polynomial operator- (const polynomial& other) const
    {
        return *this + (-other);
    }

    polynomial operator* (const polynomial& other) const
    {
        return polynomial(mul(P, other.P));
    }
};
template<typename V, typename Transform>
poly_multiplies<V, Transform> polynomial<V, Transform>::mul;

// -$- ktl/math/poly.cpp -$-


// -*- ktl/util/extio.cpp -*-

#include <iostream>
#include <utility>
#include <vector>
#include <set>
#include <map>

using std::ostream; using std::istream;
using std::cout; using std::cin;

template<typename T>
T sread(istream& in)
{
    T x;
    in >> x;
    return x;
}

template<typename T>
T read() { return sread<T>(cin); }

template<typename _1, typename _2>
ostream& operator<< (ostream& out, const std::pair<_1, _2>& p)
{
    return out << "[" << p.first << ", " << p.second << "]";
}

template<typename Container>
ostream& _print_container_imp (ostream& out, const Container& c)
{
    auto it = c.begin();
    out << "{" << *it;
    while(++it != c.end())
        out << ", " << *it;
    return out << "}";
}

template<typename Container, typename _Iterator = typename Container::iterator>
ostream& operator<< (ostream& out, const Container& c) { return _print_container_imp(out, c); }

// -$- ktl/util/extio.cpp -$-

#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n;
    cin >> n;

    vector<int> A(n);
    for(size_t i = 0; i < n; i++)
        cin >> A[i];

    int minim = *min_element(A.begin(), A.end()), maxim = *max_element(A.begin(), A.end());

    polynomial<int64_t, rfft<int64_t, double, 32>> P(maxim - minim);
    map<int, size_t> cnt;
    for(auto x : A)
    {
        P[x - minim]++;
        cnt[x]++;
    }

    auto P2 = P * P;

    map<int, int64_t> wae;
    for(int i = 0; i <= 2 * (maxim - minim); i++)
        wae[i + 2*minim] = P2[i];

    int64_t result = 0;
    for(size_t k = 0; k < n; k++)
    {
        result += wae[A[k]];
        if(A[k])
        {
            if(A[k] % 2 == 0)
                result -= cnt[A[k]/2];
            result -= 2 * cnt[0];
        }
        else
            result -= 1 + 2*(cnt[0] - 1) + (cnt[0] - 1);
    }

    cout << result << endl;
}
