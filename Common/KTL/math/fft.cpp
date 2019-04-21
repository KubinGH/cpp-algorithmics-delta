// Fast Fourier Transform.
// Implemented iteratively.
// real_fft<T>::operator() returns the values of polynomial A evaluated in the powers of the root of unity.
// real_fft<T>::operator[] returns the coefficients of a polynomial with given values in the powers of the root of unity.
// Complexity: O(n log n)
// Last revision: April 2019
// To do: use baby-step, giant-step to reduce the count of trigonometric operations.

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
    vector<T> convert(const vector<Ti>& iA)
    {
        vector<T> A(iA.begin(), iA.end());
        while(A.size() & (A.size()-1)) A.emplace_back(T(0));
        return A;
    }
}

template<typename T>
struct real_fft
{
    using C = complex<T>;
    static constexpr long double Q_PI = acos(-1.0L);
    static C root_of_unity(size_t k) { return C(cos(2*Q_PI / k), sin(2*Q_PI / k)); }
    static C inverse_root_of_unity(size_t k) { return T(1) / root_of_unity(k); }
    static C divide(C x, size_t n) { return x / C(n); }

    vector<C> call(vector<C> A, const function<C(size_t)>& w)
    {
        const size_t n = A.size();

        for(size_t i = 0; i < n; i++)
        {
            size_t j = fft_base::bit_reverse(i, __lg(n));
            if(i < j)
                swap(A[i], A[j]);
        }

        for(size_t block = 2; block <= n; block *= 2)
        {
            C w_b = w(block);
            for(size_t i = 0; i < n; i += block)
            {
                C t = 1;
                const size_t m = block / 2;
                for(size_t j = 0; j < m; j++)
                {
                    auto u = A[i+j], v = A[i+j+m] * t;
                    A[i+j]   = u + v;
                    A[i+j+m] = u - v;
                    t *= w_b;
                }
            }
        }

        return A;
    }

    template<typename Ti>
    vector<C> operator() (const vector<Ti>& iA)
    {
        return call(fft_base::convert<C>(iA), root_of_unity);
    }
    template<typename Ti>
    vector<C> operator[] (const vector<Ti>& iY)
    {
        auto A = call(fft_base::convert<C>(iY), inverse_root_of_unity);
        for(size_t i = 0; i < A.size(); i++)
            A[i] = divide(A[i], A.size());
        return A;
    }
};

