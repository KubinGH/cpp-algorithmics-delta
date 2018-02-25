#include <bits/stdc++.h>
#define FERTILE '$'
#define FREE_FERTILE(X, Y) (is_fertile[Y][X] and not used[Y][X])

using namespace std;

typedef unsigned short uint16_t;

int main()
{
    uint16_t tests, width, height;
    scanf("%u", &tests);
for(uint16_t t = 0; t < tests; t++)
{
    cin >> height >> width;
    uint16_t x, y;
    static bool is_fertile[300][300];
    for(x = 0; x < width; x++) for(y = 0; y < height; y++)
        is_fertile[y][x] = false;
    static char line[301];
    for(y = 0; y < height; y++)
    {
        scanf("%s", line);
        for(x = 0; x < width; x++)
        {
            is_fertile[y][x] = line[x] == FERTILE;
        }
    }
    static bool used[300][300];
    for(x = 0; x < width; x++) for(y = 0; y < height; y++)
        used[y][x] = false;
    for(x = 0; x < width - 1; x++)
    {
        for(y = 0; y < height - 1; y++)
        {
            if(FREE_FERTILE(x, y) and FREE_FERTILE(x + 1, y) and
               FREE_FERTILE(x, y + 1) and FREE_FERTILE(x + 1, y + 1))
            {
                used[y][x] = used[y][x + 1] = used[y + 1][x] = used[y + 1][x + 1] = true;
            }
        }
    }
    bool ok = true;
    for(x = 0; x < width; x++)
    {
        for(y = 0; y < height; y++)
        {
            if(FREE_FERTILE(x, y))
            {
                ok = false;
                break;
            }
        }
        if(not ok) break;
    }
    if(ok) printf("TAK\n");
    else   printf("NIE\n");
}
}
