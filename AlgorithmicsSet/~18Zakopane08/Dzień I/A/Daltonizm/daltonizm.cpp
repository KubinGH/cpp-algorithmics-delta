#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 128;
const uint32_t CACHE[] = {1, 0, 1, 2, 2, 6, 12, 18, 43, 86, 148, 326,
                          652, 1194, 2531, 5062, 9578, 19884, 39768, 76680,
                          157236, 314472, 613440, 1248198, 2496396,
                          4906266, 9932707, 19865414};

// (RG) (GB)

typedef tuple<uint32_t, uint32_t, uint32_t> tri_u32;

int main()
{
  ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  uint32_t P, T;
  cin >> P >> T;
  if(P == 1)
  {
    while(T --> 0)
    {
        static char S[MAX];
        cin >> S; uint32_t n = strlen(S);
        static bool R[MAX][MAX][MAX];
        static char U[MAX][MAX][MAX];
        static tri_u32 P[MAX][MAX][MAX];
        R[0][0][0] = true;
        for(uint32_t i = 1; i <= n; i++)
        {
            for(uint32_t m = 0; m <= i; m++)
              for(uint32_t f = 0; f <= i; f++)
            {
                bool a = false; char u = 0; tri_u32 p;
                if(S[i-1] == '(')
                {
                    if(m and R[i-1][m-1][f])
                        a = true, u = 'R', p = tri_u32{i-1, m-1, f};
                    if(m and f and R[i-1][m-1][f-1])
                        a = true, u = 'G', p = tri_u32{i-1, m-1, f-1};
                    if(f and R[i-1][m][f-1])
                        a = true, u = 'B', p = tri_u32{i-1, m, f-1};
                }
                else if(S[i-1] == ')')
                {
                    if(R[i-1][m+1][f])
                        a = true, u = 'R', p = tri_u32{i-1, m+1, f};
                    if(R[i-1][m+1][f+1])
                        a = true, u = 'G', p = tri_u32{i-1, m+1, f+1};
                    if(R[i-1][m][f+1])
                        a = true, u = 'B', p = tri_u32{i-1, m, f+1};
                }
                R[i][m][f] = a; U[i][m][f] = u; P[i][m][f] = p;
            }
        }
        if(R[n][0][0])
        {
            stack<char> O;
            uint32_t i = n, m = 0, f = 0;
            while(i)
            {
                O.push(U[i][m][f]);
                tie(i, m, f) = P[i][m][f];
            }
            while(not O.empty())
                cout << O.top(), O.pop();
            cout << "\n";
        }
        else
            cout << "rambutan\n";
    }
  }
  else
  {
    while(T --> 0)
    {
        uint32_t x;
        cin >> x;
        cout << CACHE[x] << "\n";
    }
  }
}
