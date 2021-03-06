// Fast Fourier Transform.
// Implemented iteratively.
// fft<T>::operator() returns the values of polynomial A evaluated in the powers of the root of unity.
// fft<T>::operator[] returns the coefficients of a polynomial with given values in the powers of the root of unity.
// rfft is a simple rounding wrapper.
// Complexity: O(n log n)

// Last revision: October 2019

#pragma once

#include <ext/numeric>
#include <functional>
#include <algorithm>
#include <complex>
#include <vector>
#include <cmath>
#include "../ktl_debug_mode.cpp"

using std::vector; using std::complex;
using std::size_t;
using std::acos; using std::cos; using std::sin;
using std::function; using std::plus;
using std::swap;
using __gnu_cxx::power; using std::__lg;

namespace fft_base
{
    template<typename T>
    T bit_reverse(T x, size_t lim)
    {
        if(x == 0) return 0;
        static vector<size_t> cache[32];
        if(cache[lim].empty())
            cache[lim].resize(1 << lim);
        if(cache[lim][x])
            return cache[lim][x];
        T y = 0;
        for(size_t i = 0; i < lim; i++, x >>= 1)
            if(x & 1)
                y |= (1 << (lim - i - 1));
        return cache[lim][x] = y;
    }
    template<typename T, typename Ti>
    vector<T> convert(const vector<Ti>& iA, size_t req = 0)
    {
        vector<T> A(iA.begin(), iA.end());
        while(A.size() < req or (A.size() & (A.size()-1))) A.emplace_back(T(0));
        return A;
    }

    template<size_t RootRecalc = 0, typename T>
    vector<T> cooley_tukey(vector<T> A, function<T(size_t, size_t)> w)
    {
        static_assert((RootRecalc & (RootRecalc - 1)) == 0, "RootRecalc is hardwired to be a power of two.");
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
                    if(RootRecalc and (j & (RootRecalc-1)) == 0)
                        t = w(block, j + 1);
                    else
                        t *= w_b;
                }
            }
        }

        return A;
    }
}

template<typename T, size_t RootRecalc = 16>
struct fft
{
    using C = complex<T>;
    using Convolution = plus<size_t>;
    static constexpr long double TAU = 2 * acos(-1.0L);
    static C root_of_unity(size_t k, size_t l) { return C(cos(TAU * l / k), sin(TAU * l / k)); }
    static C inverse_root_of_unity(size_t k, size_t l) { return T(1) / root_of_unity(k, l); }

    template<typename Ti>
    vector<C> operator() (const vector<Ti>& iA, size_t req = 0)
    {
        return fft_base::cooley_tukey<RootRecalc>(fft_base::convert<C>(iA, req), function<C(size_t, size_t)>(root_of_unity));
    }
    template<typename Ti>
    vector<C> operator[] (const vector<Ti>& iY)
    {
        auto A = fft_base::cooley_tukey<RootRecalc>(fft_base::convert<C>(iY), function<C(size_t, size_t)>(inverse_root_of_unity));
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
    using Convolution = plus<size_t>;

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
