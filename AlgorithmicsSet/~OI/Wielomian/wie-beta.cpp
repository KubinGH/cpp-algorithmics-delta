#include <bits/stdc++.h>

using namespace std;

struct __bit_reverse_cache
{
    vector<vector<size_t>> cache;
    __bit_reverse_cache(size_t k) : cache(k)
    {
        for(size_t l = 0; l < k; l++)
        {
            cache[l].resize(1 << l);
            for(size_t i = 0; i < (1u << l); i++)
                for(size_t e = 0; e < l; e++)
                    cache[l][i] |= (i >> e & 1) << (l-e-1);
        }
    }

    const size_t& operator() (size_t l, size_t i) const { return cache[l][i]; }
} bit_reverse(21);

vector<uint64_t> fft(vector<uint64_t> A, uint64_t w, uint64_t mod)
{
    const size_t n = A.size(), lg = __lg(n);

    for(size_t i = 0; i < n; i++)
    {
        const size_t j = bit_reverse(lg, i);
        if(i < j)
            swap(A[i], A[j]);
    }

    vector<uint64_t> W(lg+1);
    W[0] = w;
    for(size_t i = 1; i <= lg; i++)
        W[i] = W[i-1] * W[i-1] % mod;
    reverse(W.begin(), W.end());

    for(size_t k = 1, m = 1; m <= n/2; k++, m *= 2)
    {
        for(size_t i = 0; i < n; i += 2*m)
        {
            uint64_t x = 1;
            for(size_t j = 0; j < m; j++, x = x * W[k] % mod)
            {
                uint64_t u = A[i + j], v = A[i + j + m];
                A[i+j] = (u + v*x) % mod;
                A[i+j+m] = (u + v*x%mod*W[1]) % mod;
            }
        }
    }

    return A;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, q;
    cin >> n >> m >> q;

    vector<uint64_t> A(n);
    for(auto& a : A)
        cin >> a, a %= m;

    auto B = fft(A, q, m);
    rotate(B.begin(), B.begin() + 1, B.end());

    cout << accumulate(B.begin(), B.end(), 0ull) % m << endl;
    for(auto b : B)
        cout << b << ' ';
    cout << endl;
}
