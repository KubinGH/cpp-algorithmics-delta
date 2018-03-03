#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t h, w;
    cin >> h >> w;
    static array<array<int32_t, MAX>, MAX> A;
    static array<array<int32_t, MAX+1>, MAX+1> S;
    for(uint32_t y = 0; y < h; y++)
    {
        for(uint32_t x = 0; x < w; x++)
        {
            cin >> A[y][x];
            S[y+1][x+1] = S[y+1][x] + S[y][x+1] - S[y][x] + A[y][x];
        }
    }
    uint32_t q;
    cin >> q;
    for(uint32_t i = 0; i < q; i++)
    {
        uint32_t a1, b1, a2, b2;
        cin >> a1 >> b1 >> a2 >> b2; a1--; b1--; a2--; b2--;
        cout << S[a2+1][b2+1] - S[a2+1][b1] - S[a1][b2+1] + S[a1][b1] << '\n';
    }
}
