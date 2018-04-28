#include <bits/stdc++.h>
#if not(defined(_WIN32))
#define getchar getchar_unlocked
#endif

using namespace std;

typedef unsigned int uint32_t;

const size_t MAX = 2000;

uint32_t abs_diff(uint32_t a, uint32_t b)
{
    return a > b ? a - b : b - a;
}

int main()
{
    uint32_t n, m;
    cin >> n >> m; getchar();
    static bool A[MAX][MAX];
    for(uint32_t y = 0; y < n; y++)
    {
        for(uint32_t x = 0; x < m; x++)
        {
            char c = getchar();
            A[y][x] = c == '#';
        }
        getchar();
    }
    static uint32_t E[MAX];
    for(uint32_t x = 0; x < m; x++)
    {
        for(uint32_t y = 0; y < n; y++)
        {
            if(A[y][x] == 0)
            {
                E[x] = y;
                break;
            }
        }
    }
    uint32_t r = -1u;
    for(uint32_t y = 0; y < n; y++)
    {
        uint32_t c = 0;
        for(uint32_t x = 0; x < m; x++)
            c += abs_diff(E[x], y);
        r = min(r, c);
    }
    cout << r;
}
