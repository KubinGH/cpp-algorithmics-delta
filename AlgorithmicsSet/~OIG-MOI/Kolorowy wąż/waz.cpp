#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

const size_t MAXS = 500, MAX = 500000;

int main()
{
    uint32_t h, w;
    scanf("%u %u", &h, &w);
    static uint32_t A[MAXS][MAXS];
    for(uint32_t y = 0; y < h; y++)
        for(uint32_t x = 0; x < w; x++)
            scanf("%u", &A[y][x]), A[y][x]--;
    uint32_t n, m;
    scanf("%u %u ", &n, &m);
    static uint32_t R[MAX];
    uint32_t x = 0, y = 0;
    if(A[0][0] > 0 and A[0][0] < m)
        R[A[0][0]-1]++;
    for(uint32_t i = 0; i < n; i++)
    {
        char d;
        scanf("%c", &d);
        if(d == 'N') y--;
        else if(d == 'S') y++;
        else if(d == 'W') x--;
        else if(d == 'E') x++;
        if(i + A[y][x] < n and A[y][x] < m)
            R[i+A[y][x]]++;
    }
    for(uint32_t i = 0; i < n; i++)
        printf("%u ", R[i]);
}
