#include <bits/stdc++.h>
#include <functional>
#define FORCE_TRANSFORM_POLYMUL
#include <ktl/math/fft.cpp>
#include <ktl/math/poly.cpp>
#include <ktl/util/extio.cpp>

using namespace std;

template<typename T>
struct fwht
{
    using C = T;
    using Convolution = bit_xor<size_t>;
    static C root_of_unity(size_t k, size_t l) { (void)k; (void)l; return 1; }
    static C inverse_root_of_unity(size_t k, size_t l) { (void)k; (void)l; return 1; }

    template<typename Ti>
    vector<C> operator() (const vector<Ti>& iA, size_t req = 0)
    {
        return fft_base::cooley_tukey<0>(fft_base::convert<C>(iA, req), function<C(size_t, size_t)>(root_of_unity));
    }
    template<typename Ti>
    vector<C> operator[] (const vector<Ti>& iY)
    {
        auto A = fft_base::cooley_tukey<0>(fft_base::convert<C>(iY), function<C(size_t, size_t)>(inverse_root_of_unity));
        for(size_t i = 0; i < A.size(); i++)
            A[i] /= A.size();
        return A;
    }
};

int main()
{
    polynomial<double, fwht<double>> a(vector<double>{1, 2, 3, 4, 5, 6, 7, 8}), b(vector<double>{8, 7, 6, 5, 4, 3, 2, 1});
    auto c = a * b;
    cout << c.P;
}
