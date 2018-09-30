#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 17;

int32_t count_unique3(uint32_t a, uint32_t b, uint32_t c)
{
    bitset<3> v;
    v[a] = 1; v[b] = 1; v[c] = 1;
    return int32_t(v[0]) + int32_t(v[1]) + int32_t(v[2]);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n; string S;
    cin >> n >> S;
    static int32_t DP[2][3][3][3][3][3][3];
    auto clear_row = [](uint32_t i) {
        for(uint32_t a = 0; a < 3; a++)
         for(uint32_t b = 0; b < 3; b++)
          for(uint32_t c = 0; c < 3; c++)
           for(uint32_t d = 0; d < 3; d++)
            for(uint32_t e = 0; e < 3; e++)
             for(uint32_t f = 0; f < 3; f++)
                DP[i][a][b][c][d][e][f] = numeric_limits<int32_t>::min();
    };
    clear_row(1);
    for(uint32_t a = 0; a < 3; a++)
     for(uint32_t b = 0; b < 3; b++)
      for(uint32_t c = 0; c < 3; c++)
       for(uint32_t d = 0; d < 3; d++)
        for(uint32_t e = 0; e < 3; e++)
         for(uint32_t f = 0; f < 3; f++)
            if(count_unique3(a, b, c) == 3 and count_unique3(d, e, f) == 3)
                DP[1][a][b][c][d][e][f] = -6;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t v;
        if(S[i] == 'M')         v = 0;
        else if(S[i] == 'F')    v = 1;
        else                    v = 2;
        clear_row(i&1);
        int32_t p = 0, q = 0;
        for(uint32_t b = 0; b < 3; b++)
         for(uint32_t c = 0; (p = count_unique3(b, c, v)) and c < 3; c++)
          for(uint32_t e = 0; e < 3; e++)
           for(uint32_t f = 0; (q = count_unique3(e, f, v)) and f < 3; f++)
            for(uint32_t a = 0; a < 3; a++)
             for(uint32_t d = 0; d < 3; d++)
        {
            DP[i&1][b][c][v][d][e][f] = max(
                DP[i&1][b][c][v][d][e][f],
                DP[(i&1)^1][a][b][c][d][e][f] + p
            );
            DP[i&1][a][b][c][e][f][v] = max(
                DP[i&1][a][b][c][e][f][v],
                DP[(i&1)^1][a][b][c][d][e][f] + q
            );
        }
    }
    int32_t r = 0;
    for(uint32_t a = 0; a < 3; a++)
     for(uint32_t b = 0; b < 3; b++)
      for(uint32_t c = 0; c < 3; c++)
       for(uint32_t d = 0; d < 3; d++)
        for(uint32_t e = 0; e < 3; e++)
         for(uint32_t f = 0; f < 3; f++)
            r = max(r, DP[(n-1)&1][a][b][c][d][e][f]);
    cout << r;
}
