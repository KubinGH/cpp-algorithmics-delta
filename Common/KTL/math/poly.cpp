// Basic polynomial operations

// Last revision: June 2019

#pragma once

#include <vector>
#include <complex>
#include <algorithm>
#include <functional>
#include "../util/debug_macros.cpp"

using std::multiplies; using std::plus;
using std::vector;
using std::complex;
using std::max;
using std::__lg;

const size_t POLYMUL_BRUTE_LIMIT = 512;

template<typename T, typename Transform>
struct poly_multiplies
{
    Transform tr;
    using C = typename Transform::C;

    static T cast_ct(C x) { return x; }
    template<typename t>
    static T cast_ct(complex<t> x) { return x.real(); }

    vector<T> operator() (const vector<T>& P, const vector<T>& Q)
    {
        if(P.empty() or Q.empty()) return {};
        size_t n = P.size() - 1, m = Q.size() - 1, r = n + m, r2 = 1 << __lg(2*(r + 1) - 1);
        vector<T> R(r + 1);
        #ifndef FORCE_TRANSFORM_POLYMUL
        if((uint64_t)n*m < POLYMUL_BRUTE_LIMIT)
        #else
        if(false)
        #endif
        {
            typename Transform::Convolution conv;
            for(size_t i = 0; i <= n; i++)
                for(size_t j = 0; j <= m; j++)
                    R[conv(i, j)] += P[i] * Q[j];
        }
        else
        {
            auto U = tr(P, r2), V = tr(Q, r2);
            vector<C> W(r2);
            for(size_t i = 0; i < r2; i++)
                W[i] = U[i] * V[i];
            auto Rc = tr[W];
            for(size_t i = 0; i <= r; i++)
                R[i] = cast_ct(Rc[i]);
        }
        while(not R.empty() and not R.back())
            R.pop_back();
        return R;
    }
};

template<typename T>
struct _p_identity { T operator() (T x) { return x; } };

template<typename V, typename Transform, typename Convert = _p_identity<V>>
struct polynomial
{
    static poly_multiplies<V, Transform> mul;
    Convert conv;
    vector<V> P;

    polynomial() {}
    polynomial(size_t d) : P(d + 1) {}

    template<typename W>
    polynomial(const vector<W>& p)
    {
        P.resize(p.size());
        for(size_t i = 0; i < p.size(); i++)
            P[i] = conv(V(p[i]));
    }

    size_t degree() const { return P.size() - 1; }
    const V& at(size_t i) const { static V OUT = 0; return not P.empty() and i <= degree() ? P[i] : OUT; }
    V& operator[] (size_t i) { return P[i]; }
    const V& operator[] (size_t i) const { return P[i]; }

    polynomial operator+ (const polynomial& other) const
    {
        polynomial result(max(degree(), other.degree()));
        for(size_t i = 0; i <= degree(); i++)
            result[i] = conv(at(i) + other.at(i));
        return result;
    }

    polynomial operator- () const
    {
        polynomial result = *this;
        for(size_t i = 0; i <= degree(); i++)
            result[i] = conv(-result[i]);
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
template<typename V, typename Transform, typename Convert>
poly_multiplies<V, Transform> polynomial<V, Transform, Convert>::mul;

template<typename T, typename Transform, typename Convert>
polynomial<T, Transform, Convert> identity_element(multiplies<polynomial<T, Transform, Convert>>)
{
    return polynomial<T, Transform, Convert>(vector<T>({1}));
}
template<typename T, typename Transform, typename Convert>
polynomial<T, Transform, Convert> identity_element(poly_multiplies<polynomial<T, Transform, Convert>, Transform>)
{
    return polynomial<T, Transform, Convert>(vector<T>({1}));
}
