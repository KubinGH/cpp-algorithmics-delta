#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 32, MAX_E = MAX * 3;
const uint64_t MOD = 1e6 + 7;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static uint32_t A[MAX][3];
    for(uint32_t x = 0; x < n; x++)
        for(uint32_t y = 0; y < 3; y++)
            cin >> A[x][y];
    for(uint32_t a = 1; a <= 3*n; a++)
      for(uint32_t b = a+1; b <= 3*n; b++)
        for(uint32_t c = b+1; c <= 3*n; c++)
          R[1][a][b][c] = 1;

    static uint32_t R[MAX][MAX_E][MAX_E][MAX_E];
    uint32_t r = 0;
    for(uint32_t a = 1; a <= 3*n; a++)
      for(uint32_t b = a+1; b <= 3*n; b++)
        for(uint32_t c = b+1; c <= 3*n; c++)
          r += R[n][a][b][c];
    cout << r;
}
