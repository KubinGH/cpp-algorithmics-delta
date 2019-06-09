// Number Theoretic Transform
// uses the exact same implementation as FFT, except the type is mint<T> instead of complex<T>.
// The root of unity with a given power must be provided, as well as the modulus.
// Complexity: O(n log n) with a considerable constant factor, because of the modulo operations.
// Last revision: April 2019

#pragma once

#include "fft.cpp"
#include "modular.cpp"
#include "../ktl_debug_mode.cpp"

template<typename T, T Mod, T Root, size_t RootPw>
struct ntt
{
    using C = mint<T, Mod>;
    static C root_of_unity(size_t k) { return power(C(Root), RootPw / k); }
    static C inverse_root_of_unity(size_t k) { return T(1) / root_of_unity(k); }

    template<typename Ti>
    vector<C> operator() (const vector<Ti>& iA, size_t req = 0)
    {
        KTL_DEBUG_ASSERT(iA.size() <= RootPw);
        return fft_base::call(fft_base::convert<C>(iA, req, 0), function<C(size_t)>(root_of_unity));
    }
    template<typename Ti>
    vector<C> operator[] (const vector<Ti>& iY)
    {
        KTL_DEBUG_ASSERT(iY.size() <= RootPw);
        auto A = fft_base::call(fft_base::convert<C>(iY), function<C(size_t)>(inverse_root_of_unity));
        for(size_t i = 0; i < A.size(); i++)
            A[i] /= A.size();
        return A;
    }
};

using ntt_alpha = ntt<uint_fast32_t, 7340033, 5, (1 << 20)>;
