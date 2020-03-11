// does work
#include <bits/stdc++.h>

using namespace std;

struct trimatrix
{
    uint32_t t[3][3];
    uint32_t tr() const { return t[0][0] + t[1][1] + t[2][2]; }
    uint32_t det() const { return t[0][0]*(t[1][1]*t[2][2] - t[1][2]*t[2][1]) - t[0][1]*(t[1][0]*t[2][2] - t[1][2]*t[2][0]) + t[0][2]*(t[1][0]*t[2][1] - t[1][1]*t[2][0]); }
} id{{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};

trimatrix operator* (const trimatrix& A, const trimatrix& B)
{
    trimatrix C = {};
    for(size_t i = 0; i < 3; i++)
        for(size_t j = 0; j < 3; j++)
    {
        uint32_t c = 0;
        for(size_t k = 0; k < 3; k++)
            c += A.t[i][k] * B.t[k][j];
        C.t[i][j] = c;
    }
    return C;
}

struct __gen_hash
{
    trimatrix H[32];
    __gen_hash()
    {
        mt19937 gen(42);
        for(size_t i = 0; i < 32; i++)
        {
            do { for(size_t a = 0; a < 3; a++)
                for(size_t b = 0; b < 3; b++)
                    H[i].t[a][b] = gen();
            } while(H[i].det() % 2 == 0);
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
