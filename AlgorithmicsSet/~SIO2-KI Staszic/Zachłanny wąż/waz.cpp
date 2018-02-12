#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 10000;

int64_t max(int64_t a, int64_t b)
{
    return a > b ? a : b;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    uint16_t h, w;
    cin >> h >> w;
    static array<int64_t, MAX> R;
    cin >> R[0];
    int64_t c;
    for(uint16_t x = 1; x < w; x++)
    {
        cin >> c;
        R[x] = R[x-1] + c;
    }
    for(uint16_t y = 1; y < h; y++)
    {
        cin >> c;
        R[0] += c;
        for(uint16_t x = 1; x < w; x++)
        {
            cin >> c;
            R[x] = max(R[x-1], R[x]) + c;
        }
    }
    cout << R[w-1];
}
