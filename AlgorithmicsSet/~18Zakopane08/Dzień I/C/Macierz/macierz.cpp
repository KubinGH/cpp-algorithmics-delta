#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 512;

int main()
{
    uint32_t n;
    cin >> n;
    static int32_t A[MAX][MAX], L[MAX][MAX], R[MAX][MAX];
    for(uint32_t y = 1; y <= n; y++)
        for(uint32_t x = 1; x <= n; x++)
            cin >> A[y][x];
    for(uint32_t y = 0; y <= n; y++)
        for(uint32_t x = 0; x <= n; x++)
            L[y+1][x+1] = L[y][x] + A[y][x];
    for(uint32_t y = n+2; y --> 1; )
        for(uint32_t x = 0; x <= n; x++)
            R[y-1][x+1] = R[y][x] + A[y][x];
    int32_t r = 0;
    for(uint32_t x = 1; x <= n; x++)
    {
        for(uint32_t y = 1; y <= n; y++)
        {
            for(uint32_t m = 0; x + m <= n and y + m <= n; m++)
            {
                int32_t a = L[y+m+1][x+m+1] - L[y][x],
                        b = R[y-1][x+m+1] - R[y+m][x];
                r = max(r, a - b);
            }
        }
    }
    cout << r;
}
