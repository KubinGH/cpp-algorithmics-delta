#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 3042;
const uint64_t DEFAULT_B = 1LLU << 48;

template<uint64_t B>
struct fractint
{
    uint64_t A;
    fractint& operator= (fractint o) { A = o.A; return *this; }
    fractint& operator= (uint64_t o) { A = o*B; return *this; }
    fractint operator+ (fractint o) { return {A + o.A}; }
    fractint operator+ (uint64_t o) { return {A + o*B}; }
    fractint& operator+= (fractint o) { A += o.A; return *this; }
    fractint& operator+= (uint64_t o) { A += o*B; return *this; }
    fractint operator- (fractint o) { return {A - o.A}; }
    fractint operator- (uint64_t o) { return {A - o*B}; }
    fractint& operator-= (fractint o) { A -= o.A; return *this; }
    fractint& operator-= (uint64_t o) { A -= o*B; return *this; }
    fractint operator/ (uint64_t o) { return {A/o}; }
    fractint operator/ (fractint o) { return {A/o.A}; }
    fractint& operator/= (uint64_t o) { A /= o; return *this; }
    fractint& operator/= (fractint o) { A /= o.A; return *this; }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k; k--;
    cout << fixed << setprecision(13);
    static uint64_t W[MAX], P[MAX];
    for(uint32_t i = 0; i < n; i++)
        cin >> W[i];
    partial_sum(W, W + n, P + 1);
    static fractint<DEFAULT_B> Q[MAX][MAX], S[MAX][MAX], Z[MAX][MAX];
    for(uint32_t i = 0; i < n; i++)
        Q[i][i+1] = 0;
    Q[k][k+1] = 1; Z[k][k+2] = 1; S[k][k+1] = 1;
    for(uint32_t d = 2; d <= n; d++)
    {
        for(uint32_t i = 0; i <= n - d; i++)
        {
            uint32_t j = i + d;
            uint32_t lo = i+1, hi = j;
            while(lo < hi)
            {
                uint32_t m = (lo + hi) / 2;
                if(P[m] - P[i] > P[j] - P[m])
                    hi = m;
                else
                    lo = m + 1;
            } // lo -> first where P[lo] - P[i] > P[j] - P[lo]
            Q[i][j] += Z[i][j] - Z[i][lo];
            if(P[lo-1] - P[i] == P[j] - P[lo-1])
                lo--;
            Q[i][j] += S[i+1][j] - S[lo][j];
            Q[i][j] /= d - 1;
            Z[i][j+1] = Z[i][j] + Q[i][j];
            S[i][j] = S[i+1][j] + Q[i][j];
        }
    }
    cout << (double)Q[0][n].A / (double)DEFAULT_B;
}
