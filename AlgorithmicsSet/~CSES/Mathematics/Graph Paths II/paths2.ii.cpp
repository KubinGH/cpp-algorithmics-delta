#include <bits/stdc++.h>
#include <ext/numeric>

// -*- ktl/ktl_debug_mode.cpp -*-

#ifdef _KTL_DEBUG
#include <cassert>
#define KTL_DEBUG_ASSERT(__EXPR) assert(__EXPR)
#else
#define KTL_DEBUG_ASSERT(_)
#endif

// -$- ktl/ktl_debug_mode.cpp -$-

// -*- ktl/math/matrix.cpp -*-

#include <algorithm>
#include <numeric>
#include <cstdint>
#include <vector>
#include <memory>

using std::size_t;
using std::vector;
using std::copy; using std::fill; using std::min;
using std::multiplies;
using std::numeric_limits;
using std::__lg;

template<typename T>
struct matrix
{
    size_t h, w;
    vector<T> A;
    bool is_identity = false;
    matrix() : h(0), w(0), is_identity(true) {}
    matrix(size_t _w, size_t _h) : h(_h), w(_w), A(w*h) {}
    matrix(const vector<vector<T>>& a) : w(a[0].size()), h(a.size()), A(w*h)
    {
        KTL_DEBUG_ASSERT(all_of(a.begin(), a.end(), [&](const vector<T>& v) { return v.size() == a[0].size(); }));
        size_t i = 0;
        for(const auto& o : a)
            for(const auto& x : o)
                A[i++] = x;
    }
    T& operator() (size_t i, size_t j) { return A[w*i + j]; }
    const T& operator() (size_t i, size_t j) const { return A[w*i + j]; }
};

namespace std
{
    template<typename T>
    struct multiplies<matrix<T>>
    {
        matrix<T> operator() (const matrix<T>& A, const matrix<T>& B)
        {
            if(A.is_identity) return B;
            if(B.is_identity) return A;
            KTL_DEBUG_ASSERT(A.w == B.h);
            const size_t d = A.w;
            matrix<T> C(B.w, A.h);
            for(size_t i = 0; i < C.h; i++)
                for(size_t j = 0; j < C.w; j++)
                    for(size_t k = 0; k < d; k++)
                        C(i, j) += A(i, k) * B(k, j);
            return C;
        }
    };
    template<typename T>
    matrix<T> identity_element(multiplies<matrix<T>>) { return matrix<T>(); }
}
template<typename T>
struct matrix_minsum_multiplies
{
    matrix<T> operator() (const matrix<T>& A, const matrix<T>& B)
    {
        if(A.is_identity) return B;
        if(B.is_identity) return A;
        KTL_DEBUG_ASSERT(A.w == B.h);
        const size_t d = A.w;
        matrix<T> C(B.w, A.h);
        for(size_t i = 0; i < C.h; i++)
          for(size_t j = 0; j < C.w; j++)
        {
            T v = numeric_limits<T>::max();
            for(size_t k = 0; k < d; k++)
                v = min(v, A(i, k) + B(k, j));
            C(i, j) = v;
        }
        return C;
    }
};
template<typename T>
matrix<T> identity_element(matrix_minsum_multiplies<T>) { return matrix<T>(); }

template<typename T, T Mod>
struct matrix_mod_multiplies
{
    matrix<T> operator() (const matrix<T>& A, const matrix<T>& B)
    {
        if(A.is_identity) return B;
        if(B.is_identity) return A;
        KTL_DEBUG_ASSERT(A.w == B.h);
        const size_t d = A.w;
        matrix<T> C(B.w, A.h);
        const size_t g = (1 << __lg(numeric_limits<T>::max() / (Mod*Mod) - 1)) - 1;
        for(size_t i = 0; i < C.h; i++)
            for(size_t j = 0; j < C.w; j++)
                for(size_t k = 0; k < d; k++)
        {
            C(i, j) += A(i, k) * B(k, j);
            if(((d-1 - k) & g) == 0)
                C(i, j) %= Mod;
        }
        return C;
    }
};
template<typename T, T Mod>
matrix<T> identity_element(matrix_mod_multiplies<T, Mod>) { return matrix<T>(); }

// -$- ktl/math/matrix.cpp -$-


using namespace std;
using __gnu_cxx::power;

constexpr int64_t oo = INT64_MAX / 3 + 0xD;

template<typename T>
struct matrix_tropical_multiplies
{
    matrix<T> operator() (const matrix<T>& A, const matrix<T>& B)
    {
        if(A.is_identity) return B;
        if(B.is_identity) return A;
        KTL_DEBUG_ASSERT(A.w == B.h);
        const size_t d = A.w;
        matrix<T> C(B.w, A.h);
        for(size_t i = 0; i < C.h; i++)
          for(size_t j = 0; j < C.w; j++)
        {
            T v = +oo;
            for(size_t k = 0; k < d; k++)
                v = min(v, A(i, k) + B(k, j));
            C(i, j) = v;
        }
        return C;
    }
};
template<typename T>
matrix<T> identity_element(matrix_tropical_multiplies<T>) { return matrix<T>(); }

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, k;
    cin >> n >> m >> k;

    matrix<int64_t> A(n, n);
    fill(A.A.begin(), A.A.end(), +oo);

    for(size_t i = 0; i < m; i++)
    {
        size_t u, v; int64_t w;
        cin >> u >> v >> w; u--; v--;
        A(u, v) = min(A(u, v), w);
    }

    auto d = power(A, k, matrix_tropical_multiplies<int64_t>{})(0, n - 1);
    cout << (d >= +oo ? -1 : d) << endl;
}
