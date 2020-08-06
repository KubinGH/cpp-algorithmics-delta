#include <bits/stdc++.h>

using namespace std;

const size_t N = 1024;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t M, R;
    cin >> M >> R;

    static char type[N][N];
    for(size_t r = 0; r < R; r++)
        for(size_t m = 0; m < M; m++)
            cin >> type[r][m];

    int result[N][N];
    for(size_t r = R; r --> 0; )
    {
        for(size_t m = M; m --> 0; )
        {
            if(type[r][m] == 'M')
                result[r][m] = result[r][m+1];
            else if(type[r][m] == 'R')
                result[r][m] = result[r+1][m];
            else if(type[r][m] == 'O')
            {
                int64_t a = r, b = m+1, c = r+1, d = m;
                while(a != c or b != d)
                {
                    if(type[a][b] == 'R' or type[a][b] == 'O') a++;
                    else b++;
                    if(type[c][d] == 'M' or type[c][d] == 'O') d++;
                    else c++;
                }
                result[r][m] = result[r][m+1] + result[r+1][m] - result[a][b];
            }
            result[r][m]++;
        }
    }
    for(size_t r = 0; r < R; r++, cout << '\n')
        for(size_t m = 0; m < M; m++, cout << ' ')
            cout << result[r][m];
}
