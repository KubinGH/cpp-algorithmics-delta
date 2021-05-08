#include <bits/stdc++.h>
#include <ext/numeric>
#include <ktl/math/matrix.cpp>

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
