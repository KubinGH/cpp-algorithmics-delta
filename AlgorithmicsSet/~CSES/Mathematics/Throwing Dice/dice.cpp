#include <bits/stdc++.h>

using namespace std;

constexpr uint mod = 1e9 + 7;

template<typename T, size_t N, size_t M>
using matrix = array<array<T, M>, N>;

template<typename T, size_t N, size_t M, size_t K>
struct matmulmod_op
{
    matrix<T, N, K> operator() (const matrix<T, N, M>& a, const matrix<T, M, K>& b)
    {
        matrix<T, N, K> c = {};
        for(size_t i = 0; i < N; i++)
            for(size_t j = 0; j < K; j++)
                for(size_t k = 0; k < M; k++)
                    c[i][j] += (uint64_t) a[i][k] * b[k][j] % mod, c[i][j] %= mod;
        return c;
    }
};

template<typename T, typename Monoid, typename Tk = size_t>
T power(T n, Tk k, Monoid f, T r = T(1))
{
    while(k)
    {
        if(k % 2)
            r = f(r, n);
        n = f(n, n);
        k /= 2;
    }
    return r;
}

template<typename T, size_t N>
matrix<T, N, N> identity_matrix()
{
    array<array<T, N>, N> id = {};
    for(size_t i = 0; i < N; i++)
        id[i][i] = 1;
    return id;
}

template<typename T, size_t N, size_t M, size_t K>
matrix<T, N, K> operator* (const matrix<T, N, M>& a, const matrix<T, M, K>& b) { return matmulmod_op<T, N, M, K>{}(a, b); }

template<typename T, size_t N, typename Tk>
matrix<T, N, N> matpower(const matrix<T, N, N>& M, Tk k)
{
    return power(M, k, matmulmod_op<T, N, N, N>{}, identity_matrix<T, N>());
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    constexpr matrix<uint, 6, 6> M = {{
        {0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1}
    }};
    constexpr matrix<uint, 6, 1> V = {{{0}, {0}, {0}, {0}, {0}, {1}}};

    uint64_t n;
    cin >> n;

    cout << (matpower(M, n) * V)[5][0] << endl;
}
