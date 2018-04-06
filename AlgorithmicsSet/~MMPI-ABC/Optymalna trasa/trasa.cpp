#include <bits/stdc++.h>

using namespace std;

struct dt
{
    uint32_t max_value, ways;
};

const size_t MAX = 1000;
const uint32_t LIM = 1e9 + 9;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t h, w;
    cin >> h >> w;
    static dt result[MAX][MAX];
    for(uint32_t y = 0; y < h; y++)
    {
        for(uint32_t x = 0; x < w; x++)
        {
            char c;
            cin >> c;
            uint32_t value = c == '*';
            if(x == 0 and y == 0)
            {
                result[y][x].ways = 1;
                result[y][x].max_value = value;
            }
            else if(x == 0)
                result[y][x] = result[y-1][x];
            else if(y == 0)
                result[y][x] = result[y][x-1];
            else
            {
                if(result[y][x-1].max_value > result[y-1][x].max_value)
                    result[y][x] = result[y][x-1];
                else if(result[y][x-1].max_value < result[y-1][x].max_value)
                    result[y][x] = result[y-1][x];
                else
                {
                    result[y][x] = result[y][x-1];
                    result[y][x].ways += result[y-1][x].ways;
                    result[y][x].ways %= LIM;
                }
            }
            result[y][x].max_value += value;
        }
    }
    cout << result[h-1][w-1].ways;
}
