#include <bits/stdc++.h>

using namespace std;

constexpr long double Q_PI = acos(-1.0L);

namespace fft_base
{
    template<typename T>
    vector<T> fft(const vector<T>& A, const function<T(size_t)>& w)
    {
        const size_t n = A.size();
        if(n == 1)
            return {A[0]};

        const size_t m = n / 2;
        vector<T> A0(m), A1(m);
        for(size_t i = 0; i < m; i++)
            A0[i] = A[2*i], A1[i] = A[2*i+1];
        auto Y0 = fft(A0, w);
        auto Y1 = fft(A1, w);

        vector<T> Y(n);
        T w_n = w(n), t = w_n;
        for(size_t i = 0; i < m; i++)
        {
            Y[i]   = Y0[i] + Y1[i] * t;
            Y[i+m] = Y0[i] - Y1[i] * t;
            t *= w_n;
        }

        return Y;
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
    static_assert(is_floating_point<T>::value, "Real FFT must use floating-point type");
    using C = complex<T>;
    static C root_of_unity(size_t k) { return C(cos(2*Q_PI / k), sin(2*Q_PI / k)); }
    static C inverse_root_of_unity(size_t k) { return root_of_unity(-k); }
    static C divide(C x, size_t n) { return x / C(n); }

    template<typename Ti>
    vector<C> operator() (const vector<Ti>& iA) // fourier transform
    {
        return fft_base::fft<C>(fft_base::convert<C>(iA), root_of_unity);
    }
    template<typename Ti>
    vector<C> operator[] (const vector<Ti>& iY) // inverse fourier transform
    {
        auto A = fft_base::fft<C>(fft_base::convert<C>(iY), inverse_root_of_unity);
        for(size_t i = 0; i < A.size(); i++)
            A[i] = divide(A[i], A.size());
        return A;
    }
};

int main()
{
    vector<uint32_t> A = {1, 4, 6};
    auto Y = real_fft<double>{}(A);
    for(auto y : Y)
        cout << y << " "; cout << endl;
    auto A1 = real_fft<double>{}[Y];
    for(auto a : A1)
        cout << a << " "; cout << endl;
}
