#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

const uint MOD = 1e9 + 7;

vector<size_t> prefixosuffixes(const string& S)
{
    const size_t n = S.size();
    vector<size_t> P(n);
    P[0] = 0;
    for(size_t i = 1; i < n; i++)
    {
        P[i] = P[i-1];
        while(P[i] and S[P[i]] != S[i])
            P[i] = P[P[i] - 1];
        if(S[i] == S[P[i]])
            P[i]++;
    }
    return P;
}

vector<size_t> matching_shifts(string S, string Z)
{
    const size_t n = S.size();

    vector<size_t> T; T.reserve(n);

    auto pat = S + "#" + Z + Z;
    auto patpat = prefixosuffixes(pat);

    const size_t patset = 2*n;
    for(size_t i = 0; i < n; i++)
        if(patpat[i + patset] == n)
            T.push_back(i);

    return T;
}

uint pow_m1(uint x) {
    return x % 2 ? MOD - 1 : 1;
}

uint mod_mul(uint a, uint b)
{
    return (uint64_t)a * b % MOD;
}

uint calcW(uint n, uint k)
{
    uint64_t W = 1; // w_0

    for(size_t e = 0; e < k; e++)
    {
        uint64_t sigma = W + mod_mul(MOD + W - pow_m1(e), n - 1);
        W = (MOD + sigma - W) % MOD;
    }

    return W;
}

struct matrix3
{
    uint A[9] = {0};

    matrix3()
    {
        fill(A, A + 9, 0);
    }

    matrix3(vector<uint> a)
    {
        for(size_t i = 0; i < 3; i++)
            for(size_t j = 0; j < 3; j++)
                (*this)(i, j) = a[3*i+j];
    }

    uint& operator() (size_t y, size_t x) { return A[y*3+x]; }
    const uint& operator() (size_t y, size_t x) const { return A[y*3+x]; }

    friend matrix3 operator* (const matrix3& A, const matrix3& B)
    {
        matrix3 C;
        assert(count(C.A, C.A+9, 0) == 9);
        for(size_t i = 0; i < 3; i++)
          for(size_t j = 0; j < 3; j++)
        {
            for(size_t k = 0; k < 3; k++)
                C(i, j) += mod_mul(A(i, k), B(k, j));
            C(i, j) %= MOD;
        }
        return C;
    }
};
matrix3 identity_element(multiplies<matrix3>)
{
    return matrix3({
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    });
}

uint lrW(uint n, uint k, uint w0, uint w1, uint w2)
{
    // w[k+3] = (n - 1) w[k+2] + w[k+1] + (n - 1) w[k]

    matrix3 M = matrix3({
        0, 1, 0,
        0, 0, 1,
        MOD - (n - 1), 1, n - 1
    });

    auto P = power(M, k);

    return (mod_mul(w0, P(0, 0)) + mod_mul(w1, P(0, 1)) + mod_mul(w2, P(0, 2))) % MOD;
}


int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    uint n, k;

    cin >> n >> k;

    uint w[] = {calcW(n, 0), calcW(n, 1), calcW(n, 2)};
    uint W;

    W = lrW(n, k, w[0], w[1], w[2]);

    string S, Z;
    cin >> S >> Z;

    uint result = 0;
    for(auto t : matching_shifts(S, Z))
    {
        result += MOD + W - (t ? pow_m1(k) : 0);
        result %= MOD;
    }
    cout << result << '\n';
}
