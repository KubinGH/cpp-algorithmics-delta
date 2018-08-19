#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t w, h;
    cin >> h >> w;
    static bitset<MAX> type[MAX];
    for(uint32_t y = 0; y < h; y++)
      for(uint32_t x = 0; x < w; x++)
    {
        char c;
        cin >> c;
        type[y][x] = (c == 'N');
    }
}
