#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e5 + 16, MOD = 1e9 + 7;

int main()
{
    uint32_t n;
    static char S[MAX];
    cin >> n >> S;
    static bitset<256> U;
    static uint32_t T[256];
    uint32_t k = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        unsigned char c = S[i];
        if(not U[c])
            U[c] = true, T[c] = k++;
    }
    vector<uint32_t> A(k, 0), B(k, 0);
    map<vector<uint32_t>, uint32_t> M; M[B]++;
    uint32_t r = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        A[T[(unsigned char)S[i]]]++;
        uint32_t m = -1u;
        for(uint32_t j = 0; j < k; j++)
            m = min(m, A[j]);
        for(uint32_t j = 0; j < k; j++)
            B[j] = A[j] - m;
        r += M[B], r %= MOD;
        M[B]++;
    }
    cout << r;
}
