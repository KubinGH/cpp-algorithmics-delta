#include<iostream>
#include<cstdint>
#include<ext/numeric>

using namespace std;
using namespace __gnu_cxx;

const uint64_t MOD = 123456789;

struct matrix 
{
    uint64_t m[2][2] = {{0, 0}, {0, 0}};
    matrix(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
    {
        m[0][0] = a; m[0][1] = b; m[1][0] = c; m[1][1] = d;
    }
    matrix() {}
};
matrix operator* (matrix a, matrix b)
{
    matrix c;
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            for(int k = 0; k < 2; k++)
                c.m[i][j] = (c.m[i][j] + a.m[i][k]*b.m[k][j]) % MOD;
    return c;
}

matrix identity_element(multiplies<matrix>) { return matrix(1, 0, 0, 1); }

int main()
{
    uint32_t n;
    cin >> n;
    matrix M(1, 1, 1, 0);
    matrix P = power(M, n-1);
    cout << (P.m[1][0] + P.m[1][1]) % MOD;
}