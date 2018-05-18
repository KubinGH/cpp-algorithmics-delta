#include <bits/stdc++.h>
//#define RANDTEST

using namespace std;

const size_t MAX = 1e4, MAX_C = 26;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    static char A[MAX+1];
    cin >> A;
    uint32_t n = strlen(A);
    for(uint32_t i = 0; i < n; i++)
        A[i] -= 'a';
#ifdef RANDTEST
{
    static uint16_t R[MAX][MAX];
    uint16_t r = 1;
    for(uint32_t i = 0; i < n-1; i++)
    {
        for(uint32_t j = i+1; j < n; j++)
        {
            if(A[i] == A[j])
            {
                R[i][j] = 0;
                continue;
            }
            R[i][j] = 2;
            for(uint32_t p = 0; p < i; p++)
            {
                if(A[i] == A[p] or A[j] == A[p])
                    continue;
                R[i][j] = max(R[i][j], uint16_t(R[p][i] + 1));
            }
            r = max(R[i][j], r);
            //cerr << R[i][j] << " ";
        }
        //cerr << endl;
    }
    cerr << n - r << endl;
}
#endif
    static uint16_t R[MAX][MAX];
    static uint32_t L[MAX_C];
    fill(begin(L), end(L), -1u);
    uint16_t r = 1;
    for(uint32_t i = 0; i < n-1; i++)
    {
        for(uint32_t j = i+1; j < n; j++)
        {
            if(A[i] == A[j])
            {
                R[i][j] = 0;
                continue;
            }
            R[i][j] = 2;
            for(char p = 0; p < (char)MAX_C; p++)
            {
                if(A[i] == p or A[j] == p or L[(size_t)p] == -1u)
                    continue;
                R[i][j] = max(R[i][j], uint16_t(R[L[(size_t)p]][i] + 1));
            }
            r = max(R[i][j], r);
            //cerr << R[i][j] << " ";
        }
        //cerr << endl;
        L[(size_t)A[i]] = i;
    }
    cout << n - r;
}
