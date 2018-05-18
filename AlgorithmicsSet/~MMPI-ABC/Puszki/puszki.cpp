#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500, MAX_K = 501;

uint64_t S[MAX+1][MAX+1];
uint64_t sum(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)
{
    return S[y2+1][x2+1] - S[y2+1][x1] - S[y1][x2+1] + S[y1][x1];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    if(k > n) n = k;
    static uint64_t A[MAX][MAX];
    for(uint32_t y = 0; y < n; y++)
    {
        for(uint32_t x = 0; x < n - y; x++)
        {
            uint32_t ax = x, ay = n - y - 1 - x;
            cin >> A[ay][ax];
        }
    }
    for(uint32_t y = 0; y < n; y++)
        for(uint32_t x = 0; x < n; x++)
            S[y+1][x+1] = A[y][x] + S[y][x+1] + S[y+1][x] - S[y][x];
    auto D = [&](uint32_t i) { return make_pair(i, n - i - 1); };
    static uint64_t R[2][MAX][MAX];
    for(uint32_t ki = 1; ki <= k; ki++)
    {
        for(uint32_t d = 0; d < n; d++)
        {
            for(uint32_t i = 0; i < n - d; i++)
            {
                uint32_t j = i + d;
                R[ki%2][i][j] = R[1-ki%2][i][j];
                for(uint32_t p = i; p <= j; p++)
                {
                    uint32_t px, py; tie(px, py) = D(p);
                    uint64_t t = sum(px - (p - i), py - (j - p), px, py);
                    t += max((p>i)*R[1-ki%2][i][p-1], (p<j)*R[1-ki%2][p+1][j]);
                    R[ki%2][i][j] = max(R[ki%2][i][j], t);
                }
            }
        }
    }
    cout << R[k&1][0][n-1];
}
