#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 2048;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static int64_t A[MAX], B[MAX];
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    for(uint32_t i = 0; i < n; i++)
        cin >> B[i];
    static int64_t R[MAX][MAX];
    static uint32_t L[MAX][MAX];
    for(uint32_t i = 0; i < n; i++)
    {
        for(uint32_t j = 0; j < n; j++)
        {
            if(R[i][j+1] > R[i+1][j+1])
                R[i+1][j+1] = R[i][j+1], L[i+1][j+1] = 0b10;
            if(R[i+1][j] > R[i+1][j+1])
                R[i+1][j+1] = R[i+1][j], L[i+1][j+1] = 0b01;
            if(A[i] == B[j] and R[i][j] + A[i] > R[i+1][j+1])
                R[i+1][j+1] = R[i][j] + A[i], L[i+1][j+1] = 0b11;
        }
    }
    uint32_t i = n, j = n, k = 0;
    static int64_t S[MAX];
    while(i > 0 or j > 0)
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
    cout << k << "\n";
    reverse(S, S + k);
    for(i = 0; i < k; i++)
        cout << S[i] << " ";
}
