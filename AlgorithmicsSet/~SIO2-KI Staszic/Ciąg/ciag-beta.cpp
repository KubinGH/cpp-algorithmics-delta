#include <bits/stdc++.h>

using namespace std;

constexpr uint mod = 1e9;
const size_t D = 50;

template<typename T, size_t N, size_t M>
using matrix = array<array<T, M>, N>;

template<typename T, size_t N, size_t M, size_t K>
struct matmulmod
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

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t cases;
    cin >> cases;

    while(cases --> 0)
    {
        size_t n;
        cin >> n;

        matrix<uint, D, 1> V = {};
        for(size_t i = 0; i < n; i++)
            cin >> V[i][0];

        matrix<uint, D, D> L = {};
        for(size_t i = 0; i+1 < n; i++)
            L[i][i+1] = 1;
        for(size_t i = 0; i < n; i++)
            cin >> L[n-1][n-i-1];

        size_t k;
        cin >> k; k--;

        auto Lk = power(L, k, matmulmod<uint, D, D, D>{}, identity_matrix<uint, D>());
        auto Vk = matmulmod<uint, D, D, 1>{}(Lk, V);

        cout << Vk[0][0] << '\n';
    }
}
