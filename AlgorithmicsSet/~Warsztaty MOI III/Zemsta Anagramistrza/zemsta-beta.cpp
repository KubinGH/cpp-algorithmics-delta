#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000, MAX_C = 26;

int main()
{
    static char A[MAX], B[MAX];
    cin >> A >> B;
    uint32_t n = strlen(A), m = strlen(B);
    static uint32_t X[MAX][MAX_C], Y[MAX][MAX_C];
    for(uint32_t i = 1; i <= n; i++)
    {
        A[i-1] -= 'a';
        copy(&X[i-1][0], &X[i-1][26], &X[i][0]);
        X[i][(size_t)A[i-1]]++;
    }
    for(uint32_t i = 1; i <= m; i++)
    {
        B[i-1] -= 'a';
        copy(&Y[i-1][0], &Y[i-1][26], &Y[i][0]);
        Y[i][(size_t)B[i-1]]++;
    }
    uint32_t r = 0;
    uint32_t rai = -1u, raj = -1u, rbi = -1u, rbj = -1u;
    for(uint32_t i = 0; i < n; i++)
    {
        for(uint32_t j = 0; j < m; j++)
        {
            for(uint32_t d = r+1; d <= min(n - i, m - j); d++)
            {
                for(uint32_t c = 0; c < MAX_C; c++)
                {
                    if(X[i+d][c] - X[i][c] != Y[j+d][c] - Y[j][c])
                        goto fail;
                }
                if(d > r)
                {
                    rai = i, raj = i+d-1;
                    rbi = j; rbj = j+d-1;
                    r = d;
                }
            fail:;
            }
        }
    }
    cout << r << "\n";
    if(r > 0)
    {
        for(uint32_t i = rai; i <= raj; i++)
            cout << char(A[i]+'a'); cout << "\n";
        for(uint32_t i = rbi; i <= rbj; i++)
            cout << char(B[i]+'a');
    }
}
