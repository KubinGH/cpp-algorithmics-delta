#include <bits/stdc++.h>
#ifdef _WIN32
typedef double lfloat;
#else
typedef long double lfloat;
#endif

using namespace std;

const size_t MAX = 1 << 6;

uint32_t popcount(uint32_t x) { return __builtin_popcount(x); }

int main()
{
  ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  uint32_t t;
  cin >> t;
  while(t --> 0)
  {
    static char I[MAX];
    cin >> I; uint32_t n = strlen(I);
    if(n >= MAX)
    {
        cout << "10.0";
        continue;
    }
    static uint32_t A[MAX];
    for(uint32_t i = 0; i < n; i++)
        A[i] = I[i] - '0';
    static uint64_t DP[MAX][10][1 << 10][2];
    for(uint32_t i = 0; i < n; i++)
      for(uint32_t d = 0; d < 10; d++)
        for(uint32_t u = 0; u < (1u << 10); u++)
          for(uint32_t s = 0; s < 2; s++)
            DP[i][d][u][s] = 0;
    for(uint32_t d = 0; d < A[0]; d++)
        DP[n-1][d][(d ? (1u << d) : 0)][false] = 1;
    DP[n-1][A[0]][1u << A[0]][true] = 1;
    for(uint32_t i = n; i --> 1; )
    {
        for(uint32_t c = 0; c < 10; c++)
        {
            for(uint32_t u = 0; u < (1u << 10); u++)
            {
                for(uint32_t x = 0; x < 10; x++)
                {
                    //if(u == 0) cout << i << " " << c << " -> " << x << " (" << A[n-i] << ")" << endl;
                    uint32_t xu;
                    if(u or x) xu = u | (1u << x);
                    else xu = 0;
                    if(x < A[n-i])
                    {
                        //if(u == 0) cout << "t1" << endl;
                        DP[i-1][x][xu][false] +=
                            DP[i][c][u][false] + DP[i][c][u][true];
                    }
                    else if(x == A[n-i])
                    {
                        //if(u == 0) cout << "t2" << endl;
                        DP[i-1][x][xu][false] += DP[i][c][u][false];
                        DP[i-1][x][xu][true] += DP[i][c][u][true];
                    }
                    else
                    {
                        //if(u == 0) cout << "t3" << endl;
                        DP[i-1][x][xu][false] += DP[i][c][u][false];
                    }
                }
            }
        }
    }
    lfloat s = 1, t = 0;
    for(uint32_t c = 0; c < 10; c++)
    {
        for(uint32_t u = 0; u < (1u << 10); u++)
        {
            //if(DP[0][c][u][false])
            //    cout << c << "/" << bitset<10>(u) << ": " << DP[0][c][u][false] << endl;
            s += popcount(u) * DP[0][c][u][false];
            t += DP[0][c][u][false];
        }
    }
    //cout << s << " " << t << endl;
    cout << fixed << setprecision(15) << s / t << "\n";
  }
}
