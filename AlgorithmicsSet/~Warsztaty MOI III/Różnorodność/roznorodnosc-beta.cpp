#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e4, MAX_C = 26;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    static char S[MAX+1];
    cin >> S;
    uint32_t n = strlen(S);
    static uint32_t A[MAX], R[MAX+1][MAX_C][MAX_C];
    for(uint32_t i = 0; i < n; i++)
        A[i] = S[i] - 'a';
    for(uint32_t i = 1; i <= n; i++)
    {
        for(uint32_t a = 0; a < MAX_C; a++) for(uint32_t b = 0; b < MAX_C; b++)
        {
            R[i][a][b] = max(R[i][a][b], R[i-1][a][b]);
            if(a == b)
                continue;
            else if(A[i-1] != a and A[i-1] != b)
                R[i][b][A[i-1]] = max(R[i][b][A[i-1]], R[i-1][a][b] + 1);
        }
    }
    uint32_t r = 0;
    for(uint32_t a = 0; a < MAX_C; a++) for(uint32_t b = 0; b < MAX_C; b++)
        r = max(r, R[n][a][b]);
    cout << n - r;
}
