#include <bits/stdc++.h>
#define SUMRECT(a1, b1, a2, b2) (S[b2+1][a2+1] + S[b1][a1] - S[b1][a2+1] - S[b2+1][a1])

using namespace std;

const size_t MAX = 1000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    int32_t r;
    cin >> n >> r;
    static array<array<uint32_t, MAX>, MAX> A;
    static array<array<uint32_t, MAX+1>, MAX+1> S;
    for(uint32_t y = 0; y < n; y++)
    {
        for(uint32_t x = 0; x < n; x++)
        {
            cin >> A[y][x];
            S[y+1][x+1] = S[y][x+1] + S[y+1][x] - S[y][x] + A[y][x];
        }
    }
    int32_t sn = n;
    for(int32_t y = 0; y < sn; y++)
    {
        for(int32_t x = 0; x < sn; x++)
            cout << SUMRECT(max(0, x-r), max(0, y-r), min(x+r, sn-1), min(y+r, sn-1)) << " ";
        cout << '\n';
    }
}
