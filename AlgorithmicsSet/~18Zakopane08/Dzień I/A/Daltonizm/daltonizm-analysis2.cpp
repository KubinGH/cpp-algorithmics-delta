#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 32;
const uint32_t MOD = 1e9 + 7;
const char* TXT[]  = {"R( ", "R) ", "G( ", "G) ", "B( ", "B) "};
const char* STXT[] = {"(", ")"};

uint32_t pow(uint32_t a, uint32_t b) { return b ? a*pow(a, b-1) : 1; }
typedef tuple<uint32_t, uint32_t, uint32_t> tri_u32;

int main()
{
    // (RG) (GB)
    static uint32_t A[MAX][MAX][MAX], R[MAX][MAX][MAX];
    A[0][0][0] = 1;
    cout << "0: " << 1 << endl;
    for(uint32_t n = 25; n < MAX-1; n++)
    {
        for(uint32_t m = 0; m < MAX-1; m++)
          for(uint32_t f = 0; f < MAX-1; f++)
        {
            uint32_t a = 0;
            if(m)       a += A[n-1][m-1][f];     // R(
                        a += A[n-1][m+1][f];     // R)
            if(m and f) a += A[n-1][m-1][f-1];   // G(
                        a %= MOD;
                        a += A[n-1][m+1][f+1];   // G)
            if(f)       a += A[n-1][m][f-1];     // B(
                        a += A[n-1][m][f+1];     // B)
            A[n][m][f] = a % MOD;
        }
        //cout << n << ": " << A[n][0][0] << endl;
        if(n <= 32)
        {

            uint32_t r = 0;
            static char S[MAX]; S[0] = '('; S[n-1] = ')';
            if(n>2) for(uint32_t c = 0; c < (1u << (n-2)); c++)
            {
                for(uint32_t i = 0; i < n - 2; i++)
                    S[i+1] = ((c & (1u << i)) != 0) ? '(' : ')';
                static bool R[MAX][MAX][MAX];
                static char U[MAX][MAX][MAX];
                static tri_u32 P[MAX][MAX][MAX];
                R[0][0][0] = true;
                for(uint32_t i = 1; i <= n; i++)
                {
                    if(S[i-1] == '(')
                     for(uint32_t m = 0; m <= i; m++)
                      for(uint32_t f = 0; f <= i; f++)
                    {
                        bool& a = R[i][m][f]; char& u = U[i][m][f]; tri_u32& p = P[i][m][f];
                        if(m and R[i-1][m-1][f])
                            a = true, u = 'R', p = tri_u32{i-1, m-1, f};
                        else if(m and f and R[i-1][m-1][f-1])
                            a = true, u = 'G', p = tri_u32{i-1, m-1, f-1};
                        else if(f and R[i-1][m][f-1])
                            a = true, u = 'B', p = tri_u32{i-1, m, f-1};
                        else
                            a = false;
                    }
                    else if(S[i-1] == ')')
                     for(uint32_t m = 0; m <= i; m++)
                      for(uint32_t f = 0; f <= i; f++)
                    {
                        bool& a = R[i][m][f]; char& u = U[i][m][f]; tri_u32& p = P[i][m][f];
                        if(R[i-1][m+1][f])
                            a = true, u = 'R', p = tri_u32{i-1, m+1, f};
                        else if(R[i-1][m+1][f+1])
                            a = true, u = 'G', p = tri_u32{i-1, m+1, f+1};
                        else if(R[i-1][m][f+1])
                            a = true, u = 'B', p = tri_u32{i-1, m, f+1};
                        else
                            a = false;
                    }
                }
                if(R[n][0][0])
                    r++;
            }
            else if(n == 1) r = 0;
            else if(n == 2) r = 1;
            cout << "[" << n << ": " << r << "]" << endl;
        }
    }
}
