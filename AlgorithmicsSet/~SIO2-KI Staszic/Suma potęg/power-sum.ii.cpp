#include <bits/stdc++.h>

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

// - snip -

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

#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

const uint64_t MOD = 1e9 + 7;

struct mod_multiplies : multiplies<uint64_t>
{
    uint64_t operator() (uint64_t a, uint64_t b) { return a * b % MOD; }
} Z;

uint64_t inverse(uint64_t x)
{
    return power(x, MOD - 2, Z);
}

uint64_t factorial(uint64_t n)
{
    uint64_t r = 1;
    for(uint64_t x = 1; x <= n; x++)
        r *= x, r %= MOD;
    return r;
}

uint64_t binom(uint64_t n, uint64_t k)
{
    return factorial(n) * inverse(factorial(k) * factorial(n - k) % MOD) % MOD;
}

matrix<uint64_t> extrapolation_matrix(uint64_t n)
{
    matrix<uint64_t> M(n + 1, n + 1);
    for(size_t i = 0; i < n; i++)
        M(i, i+1) = 1;
    for(size_t i = 0; i <= n; i++)
        M(n, n - i) = (i % 2 ? MOD-1 : 1) * binom(n + 1, i + 1) % MOD;
    return M;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    uint64_t n; size_t k;
    cin >> n >> k;

    auto E = extrapolation_matrix(k + 1);
    matrix<uint64_t> V(1, k + 2);
    for(uint64_t x = 0, s = 0; x <= k + 1; x++)
    {
        s += power(x+1, k, Z); s %= MOD;
        V(x, 0) = s;
    }

    auto mul = matrix_mod_multiplies<uint64_t, MOD>{};

    auto W = mul(power(E, n - 1, mul), V);

    cout << W(0, 0) << endl;
}
