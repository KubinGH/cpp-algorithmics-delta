#include <bits/stdc++.h>
#include <ext/numeric>
#include <ktl/math/matrix.cpp>

using namespace std;
using __gnu_cxx::power;

constexpr uint mod = 1e9 + 7;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, k;
    cin >> n >> m >> k;

    matrix<uint64_t> A(n, n);

    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        A(u, v)++;
    }

    cout << power(A, k, matrix_mod_multiplies<uint64_t, mod>{})(0, n - 1) << endl;
}
