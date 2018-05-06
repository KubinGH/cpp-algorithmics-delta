#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 200;

typedef unsigned long long int uint64_t;

int main()
{
    uint64_t n;
    cin >> n;
    static uint64_t A[MAX], P[MAX+1], S[MAX][MAX];
    for(uint64_t i = 0; i < n; i++)
        cin >> A[i], P[i+1] = P[i] + A[i];
    for(uint64_t i = 0; i < n; i++)
        for(uint64_t j = i; j < n; j++)
            S[i][j] = P[j+1] - P[i];
    static uint64_t E[MAX][MAX];
    for(uint64_t i = 0; i < n; i++)
        for(uint64_t j = i; j < n; j++)
            E[i][j] = S[i][j] + j - i;
    static uint64_t R[MAX][MAX];
    for(uint64_t i = 0; i < n; i++)
        R[i][i] = 0;
    for(uint64_t i = 0; i < n - 1; i++)
        R[i][i+1] = A[i] * A[i+1];
    for(uint64_t d = 2; d <= n - 1; d++)
    {
        for(uint64_t i = 0; i < n - d; i++)
        {
            uint64_t j = i + d;
            R[i][j] = numeric_limits<uint64_t>::max();
            for(uint64_t m = i; m < j; m++)
                R[i][j] = min(R[i][j], R[i][m]+R[m+1][j] + E[i][m]*E[m+1][j]);
        }
    }
    cout << R[0][n-1];
}
