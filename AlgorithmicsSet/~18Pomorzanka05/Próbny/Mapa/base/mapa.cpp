#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500;

int main()
{

    uint32_t h, w, k;
    cin >> h >> w >> k;
    static bool A[MAX][MAX];
    for(uint32_t i = 0; i < k; i++)
    {
        uint32_t y, x;
        cin >> y >> x; y--; x--;
        A[y][x] = 1;
    }
    for(uint32_t y = 0; y < h; y++, cout << endl)
        for(uint32_t x = 0; x < w; x++)
            cout << (A[y][x] ? 'X' : '.');
}
