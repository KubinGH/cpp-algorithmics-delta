#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 5120;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    static char A[MAX], B[MAX];
    cin >> A >> B;
    uint32_t n = strlen(A), m = strlen(B);
    if(n > m) swap(A, B), swap(n, m);
    static uint32_t R[MAX][MAX], L[MAX][MAX];
    for(uint32_t i = 0; i < n; i++)
    {
        for(uint32_t j = 0; j < m; j++)
        {
            if(R[i][j+1] > R[i+1][j+1])
                R[i+1][j+1] = R[i][j+1], L[i+1][j+1] = 0b10;
            if(R[i+1][j] > R[i+1][j+1])
                R[i+1][j+1] = R[i+1][j], L[i+1][j+1] = 0b01;
            if(A[i] == B[j] and R[i][j] + 1 > R[i+1][j+1])
                R[i+1][j+1] = R[i][j] + 1, L[i+1][j+1] = 0b11;
        }
    }
    uint32_t i = n, j = m, k = 0;
    cout << R[n][m] << "\n";
    static char S[MAX];
    while(i > 0 and j > 0)
    {
        if(L[i][j] == 0b11)
            S[k] = A[i-1], k++, i--, j--;
        else if(L[i][j] == 0b10)
            i--;
        else if(L[i][j] == 0b01)
            j--;
        else
            break;
    }
    reverse(S, S + k);
    cout << S;
}
