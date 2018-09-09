#include "ckuclib.h"
#include <cstdint>
#include <vector>
#define N uint32_t(dajn())
#define E uint32_t(daje())
#define one_cost(x) jedno(x)
#define two_cost(x) dwa(x)
#define half_cost(x) polowa(x)

using namespace std;

template<typename T> T min(T a, T b, T c) { return min(a, min(b, c)); }
uint32_t log2floor(uint32_t n) { return 31 - __builtin_clz(n); }
uint32_t cellsize(uint32_t n)
{
    if(n == 0) return 0;
    else if(n == 1) return 1;
    return 2 * log2floor(n);
}

int main()
{
    uint32_t n = N;
    vector<vector<uint32_t>> DP(n+1);
    for(uint32_t i = 0; i <= n; i++)
        DP[i].resize(cellsize(i)+1);
    for(uint32_t e = 0; e <= cellsize(0); e++)
        DP[0][e] = 0;
    for(uint32_t e = 0; e <= cellsize(1); e++)
        DP[1][e] = one_cost(1);
    for(uint32_t i = 2; i <= n; i++)
    {
        uint32_t c = cellsize(i), cp = cellsize(i-1), cpp = cellsize(i-2), ch = cellsize((i+1)/2);
        for(uint32_t e = 0; e <= c; e++)
        {
            DP[i][e] = min(
                DP[i-1][min(e+1, cp)] + one_cost(i),
                DP[i-2][min(e, cpp)] + two_cost(i),
                e ? DP[(i+1)/2][min(e-1, ch)] + half_cost(i) : -1u
            );
        }
    }
    odpowiedz(DP[n][min(cellsize(n), E)]);
}
