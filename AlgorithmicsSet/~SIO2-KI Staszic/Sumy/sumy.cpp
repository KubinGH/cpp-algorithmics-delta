#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint16_t w, h;
    cin >> h >> w;
    static array<array<int16_t, MAX>, MAX> A;
    static array<array<int32_t, MAX+1>, MAX> S;
    for(uint16_t y = 0; y < h; y++)
    {
        for(uint16_t x = 0; x < w; x++)
        {
            cin >> A[y][x];
            if(x > 0) S[y][x+1] = S[y][x];
            S[y][x+1] += A[y][x];
        }
    }
    uint32_t q = 0;
    cin >> q;
    for(uint32_t qi = 0; qi < q; qi++)
    {
        uint16_t x1, y1, x2, y2;
        cin >> y1 >> x1 >> y2 >> x2;
        x1--; y1--; x2--; y2--;
        int32_t r = 0;
        for(uint16_t y = y1; y < y2 + 1; y++)
            r += S[y][x2+1] - S[y][x1];
        cout << r << '\n';
    }
}
