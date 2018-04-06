#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 50;

uint32_t sum_rect(const array<array<uint32_t, MAX+1>, MAX+1>& S,
                  uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)
{
    return S[y2+1][x2+1] + S[y1][x1] - S[y1][x2+1] - S[y2+1][x1];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t h, w;
    cin >> h >> w;
    static array<array<uint32_t, MAX>, MAX> A;
    static array<array<uint32_t, MAX+1>, MAX+1> S;
    for(uint32_t y = 0; y < h; y++)
    {
        for(uint32_t x = 0; x < w; x++)
        {
            cin >> A[y][x];
            S[y+1][x+1] = A[y][x] + S[y+1][x] + S[y][x+1] - S[y][x];
        }
    }
    static array<array<array<array<uint32_t, MAX>, MAX>, MAX>, MAX> R;
    for(uint32_t rh = 0; rh < h; rh++) for(uint32_t rw = 0; rw < w; rw++)
    {
        for(uint32_t y1 = 0; y1 < h - rh; y1++)
        {
            for(uint32_t x1 = 0; x1 < w - rw; x1++)
            {
                uint32_t x2 = x1 + rw, y2 = y1 + rh;
                uint32_t& r = R[x1][y1][x2][y2];
                if(rw == 0 and rh == 0)
                    r = 0;
                else
                {
                    r = numeric_limits<uint32_t>::max();
                    for(uint32_t cy = y1; cy < y2; cy++)
                        r = min(r, R[x1][y1][x2][cy] + R[x1][cy+1][x2][y2]);
                    for(uint32_t cx = x1; cx < x2; cx++)
                        r = min(r, R[x1][y1][cx][y2] + R[cx+1][y1][x2][y2]);
                    r += sum_rect(S, x1, y1, x2, y2);
                }
            }
        }
    }
    cout << R[0][0][w-1][h-1];
}
