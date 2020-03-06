// doesn't work
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

struct dimatrix
{
    uint32_t a, b, c, d;
    uint32_t tr() const { return (a + d) % P; }
};

dimatrix operator* (const dimatrix& A, const dimatrix& B)
{
    return {
        f((uint64_t)A.a*B.a + (uint64_t)A.b*B.c), f((uint64_t)A.a*B.b + (uint64_t)A.b*B.d),
        f((uint64_t)A.c*B.a + (uint64_t)A.d*B.c), f((uint64_t)A.c*B.b + (uint64_t)A.d*B.d)
    };
}

struct __gen_hash
{
    dimatrix H[32];
    __gen_hash()
    {
        mt19937 gen(1337);
        uniform_int_distribution<uint32_t> dis(0, P - 1);

        for(size_t i = 0; i < 32; i++)
        {
            dimatrix M = {dis(gen), dis(gen), dis(gen), dis(gen)};
            H[i] = M;
        }
    }
    const dimatrix& operator[] (size_t i) const
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
    dimatrix pref = {1, 0, 0, 1}, suff = {1, 0, 0, 1};
    for(size_t d = 1; 2*d <= n; d++)
    {
        pref = pref * mono[S[d-1]-'a'];
        suff = mono[S[n-d]-'a'] * suff;
        if(pref.tr() == suff.tr())
            result = max(result, d);
    }

    cout << result;

}
