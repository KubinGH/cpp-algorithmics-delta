#include <bits/stdc++.h>

using namespace std;

uint64_t N, M;

static bool done[16][16][16][16];
static uint64_t cache[16][16][16][16];
void CC()
{
    for(uint32_t i = 1; i <= N - 1; i++)
      for(uint32_t a = 1; a <= N; a++)
        for(uint32_t b = 1; b <= N; b++)
          for(uint32_t c = 1; c <= N; c++)
            done[i][a][b][c] = false, cache[i][a][b][c] = 0;
}
uint64_t solve4(uint32_t i, uint32_t a, uint32_t b, uint32_t c)
{
    if(i == N - 2)
        return 1;
    if(done[i][a][b][c])
        return cache[i][a][b][c];
    done[i][a][b][c] = true;
    uint64_t r = 0;
    for(uint32_t d = max(a, b)+1; d <= N; d++)
        r += solve4(i + 1, b, c, d);
    return (cache[i][a][b][c] = r);
}
uint64_t solve4_cl(uint32_t i, uint32_t a, uint32_t b, uint32_t c)
{
    if(i == N - 2)
        return 1;
    uint64_t r = 0;
    for(uint32_t d = max(a, b)+1; d <= N; d++)
        r += solve4(i + 1, b, c, d);
    return r;
}


// 1, 4, 9, 31, 88, 288
int main()
{
    cout << "1: 1" << endl;
    cout << "2: 4" << endl;
    for(N = 1; N <= 15; N++)
    {
        CC();
        uint64_t r4 = 0;
        for(uint32_t a = 1; a <= N; a++)
            for(uint32_t b = 1; b <= N; b++)
                for(uint32_t c = a+1; c <= N; c++)
                    r4 += solve4(1, a, b, c);
        static uint32_t A[128][128], V[128][128], W[128][128];
        A[0][0] = 1;
        for(uint32_t lo = 0; lo <= N; lo++)
            V[0][lo] = 1;
        for(uint32_t n = 1; n <= N; n++)
        {
            if(n < 2) for(uint32_t lo = 1; lo <= N; lo++)
                A[n][lo] = V[n-1][lo-1], V[n][lo] = V[n][lo-1] + A[n][lo];
            else
            {
                uint64_t w = A[n-2][0];
                for(uint32_t lo = 1; lo <= N; lo++)
                {
                    A[n][lo] = V[n-1][lo-1] + w;
                    w += V[n-2][lo];
                    V[n][lo] = V[n][lo-1] + A[n][lo];
                }
            }
        }
        uint64_t r = 0;
        for(uint32_t lo = 0; lo <= N; lo++)
            r += A[N][lo];
        cout << N << ": " << r4 << " / " << r << endl;
    }
}
