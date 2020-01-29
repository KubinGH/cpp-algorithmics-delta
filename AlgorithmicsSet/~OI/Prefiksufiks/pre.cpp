#include <bits/stdc++.h>

using namespace std;

const uint64_t K = 31, P = (1u << 31) - 1;
uint32_t f(uint64_t x)
{
    x++;
    x = (x >> K) + (x & P);
    x = (x >> K) + (x & P);
    return x - 1;
}

struct trimatrix
{
    uint64_t t[3][3];
    uint64_t tr() const { return f(t[0][0] + t[1][1] + t[2][2]); }
} id{{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};

trimatrix operator* (const trimatrix& A, const trimatrix& B)
{
    trimatrix C = {};
    for(size_t i = 0; i < 3; i++)
        for(size_t j = 0; j < 3; j++)
    {
        for(size_t k = 0; k < 3; k++)
            C.t[i][j] += A.t[i][k] * B.t[k][j];
        C.t[i][j] = f(C.t[i][j]);
    }
    return C;
}

struct __gen_hash
{
    trimatrix H[32];
    __gen_hash()
    {
        mt19937_64 gen(42);
        uniform_int_distribution<uint64_t> dis(0, P - 1);
        for(size_t i = 0; i < 32; i++)
        {
            for(size_t a = 0; a < 3; a++)
                for(size_t b = 0; b < 3; b++)
                    H[i].t[a][b] = dis(gen);
        }
    }
    const trimatrix& operator[] (size_t i) const
    {
        return H[i];
    }
} mono;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    string S;
    cin >> S;

    size_t result = 0;
    trimatrix pref = id, suff = id;
    for(size_t d = 1; 2*d <= n; d++)
    {
        pref = pref * mono[S[d-1]-'a'];
        suff = mono[S[n-d]-'a'] * suff;
        if(pref.tr() == suff.tr())
            result = max(result, d);
    }

    cout << result;
}
