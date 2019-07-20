// Basic polynomial operations

// Last revision: June 2019

#pragma once

#include <vector>
#include <algorithm>
#include "../util/debug_macros.cpp"

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


#include <bits/stdc++.h>
#include "../util/extio.cpp"
#include "fft.cpp"
#include "ntt.cpp"

using namespace std;

template<typename Poly>
void print_poly(const Poly& P, size_t trim = 16)
{
    if(P.P.empty()) { cout << 0 << endl; return; }
    for(size_t i = 0; i <= min(P.degree(), trim); i++)
        cout << P[i] << " ";
    if(P.degree() > trim) cout << "...";
    cout << endl;
}

/*
int main()
{
    mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());

    size_t n, m; long lo, hi;
    cin >> n >> m >> lo >> hi;

    vector<long> Pc(n + 1), Qc(m + 1);
    for(size_t i = 0; i <= n; i++)
        cin >> Pc[i];
        //Pc[i] = uniform_int_distribution<long>{lo, hi}(gen);
    for(size_t i = 0; i <= m; i++)
        cin >> Qc[i];
        //Qc[i] = uniform_int_distribution<long>{lo, hi}(gen);

    polynomial<long, rfft<long, double>> Pf(Pc), Qf(Qc);
    polynomial<long, ntt_alpha> Pn(Pc), Qn(Qc);

    print_poly(Pf);
    print_poly(Qf);
    cout << endl;
    print_poly(Pn);
    print_poly(Qn);

    auto Rf = Pf * Qf;
    auto Rn = Pn * Qn;

    cout << endl << "->" << endl;

    print_poly(Rf);
    print_poly(Rn);

    for(size_t i = 0; i <= n + m; i++)
        if(ntt_alpha::C(Rf.at(i)) != Rn.at(i))
            cout << "@ " << i << ": f" << ntt_alpha::C(Rf.at(i)) << " != n" << Rn.at(i) << endl;
}
*/
