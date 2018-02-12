#include <bits/stdc++.h>

using namespace std;

const uint64_t MAX = 1000;
const uint64_t BASE = 27;
const uint64_t MOD = 1LLU << 45;
const uint64_t IBASE = 2;

int main()
{
    uint64_t n, m;
    cin >> n >> m;
    static array<uint64_t, MAX> POW;
    POW[0] = 1;
    for(uint64_t i = 1; i <= MAX; i++)
        POW[i] = (POW[i - 1] * BASE) % MOD;
    static array<array<uint64_t, MAX>, MAX> A, B;
    char c;
    for(uint64_t y = 0; y < n; y++)
        for(uint64_t x = 0; x < n; x++)
            cin >> c, A[y][x] = c - 'a';
    for(uint64_t y = 0; y < m; y++)
        for(uint64_t x = 0; x < m; x++)
            cin >> c, B[y][x] = c - 'a';
    static array<array<uint64_t, MAX>, MAX> HA;
    static array<uint64_t, MAX> HB;
    for(uint64_t y = 0; y < n; y++)
    {
        for(uint64_t x = 0; x < m; x++)
            HA[y][0] = (HA[y][0] * BASE + A[y][x]) % MOD;
        for(uint64_t x = 1; x < n - m + 1; x++)
            HA[y][x] = ((HA[y][x - 1] - A[y][x-1] * POW[m-1]) * BASE + A[y][x+m-1]) % MOD;
    }
    for(uint64_t y = 0; y < m; y++)
        for(uint64_t x = 0; x < m; x++)
            HB[y] = ((x > 0 ? HB[y] : 0) * BASE + B[y][x]) % MOD;
    uint64_t H = 0;
    for(uint64_t y = 0; y < m; y++)
        H = (H * POW[IBASE] + HB[y]) % MOD;
    uint64_t r = 0;
    for(uint64_t x = 0; x < n - m + 1; x++)
    {
        uint64_t h = 0;
        for(uint64_t y = 0; y < m; y++)
            h = (h * POW[IBASE] + HA[y][x]) % MOD;
        if(h == H)
            r++;
        for(uint64_t y = m; y < n; y++)
        {
            h = ((h - HA[y-m][x] * POW[IBASE*(m-1)]) * POW[IBASE] + HA[y][x]) % MOD;
            if(h == H)
                r++;
        }
    }
    cout << r;
}
