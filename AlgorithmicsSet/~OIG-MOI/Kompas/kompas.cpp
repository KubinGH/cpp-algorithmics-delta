#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 300, MAX_L = 100001;

typedef unsigned int uint32_t;

int main()
{
    uint32_t h, w, len;
    scanf("%u %u %u ", &h, &w, &len);
    static char Q[MAX_L];
    fgets(Q, MAX_L - 1, stdin);
    static uint32_t A[MAX][MAX];
    uint32_t x = 0, y = 0;
    A[0][0] = 1;
    for(uint32_t i = 0, j = 2; i < len; i++)
    {
        if(Q[i] == 'N')
            y--;
        else if(Q[i] == 'S')
            y++;
        else if(Q[i] == 'W')
            x--;
        else if(Q[i] == 'E')
            x++;
        if(A[y][x] == 0)
            A[y][x] = (j++);
    }
    for(uint32_t iy = 0; iy < h; iy++)
    {
        for(uint32_t ix = 0; ix < w; ix++)
            printf("%u ", A[iy][ix]);
        printf("\n");
    }
}
