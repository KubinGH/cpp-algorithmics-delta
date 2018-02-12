#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500;
const size_t MAX_E = 2001;

int main()
{
    uint16_t w, h;
    cin >> h >> w;
    static array<array<int32_t, MAX>, MAX> A;
    static array<array<int32_t, MAX+1>, MAX> S;
    for(uint16_t y = 0; y < h; y++)
    {
        for(uint16_t x = 0; x < w; x++)
        {
            cin >> A[y][x];
            S[y][x+1] += S[y][x] + A[y][x];
        }
    }
    int32_t result = A[0][0];
    for(uint16_t x1 = 0; x1 < w; x1++)
    {
        for(uint16_t x2 = x1; x2 < w; x2++)
        {
            int32_t last = S[0][x2+1] - S[0][x1], best = last;
            for(uint16_t y = 1; y < h; y++)
            {
                int32_t current = S[y][x2+1] - S[y][x1];
                last = max(current, last + current);
                best = max(best, last);
            }
            result = max(result, best);
        }
    }
    cout << result;

}
