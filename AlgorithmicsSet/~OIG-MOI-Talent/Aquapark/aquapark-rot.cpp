#include <bits/stdc++.h>
#define clamp(n) ((n) < CLAMP_LO ? CLAMP_LO : ((n) > CLAMP_HI ? CLAMP_HI : (n)))

using namespace std;

const size_t MAX = 2001;
const int32_t CLAMP_LO = 0, CLAMP_HI = MAX-1;

uint64_t sum(const uint64_t S[MAX+1][MAX+1],
             int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    x1 = clamp(x1); x2 = clamp(x2);
    y1 = clamp(y1); y2 = clamp(y2);
    return (S[y2+1][x2+1] + S[y1][x1] - S[y2+1][x1] - S[y1][x2+1]);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, r;
    cin >> n >> r;
    static uint64_t A[MAX][MAX], S[MAX+1][MAX+1];
    auto x_transform = [=](uint32_t x, uint32_t y) { return x + n - y - 1; };
    auto y_transform = [=](uint32_t x, uint32_t y) { return x + y; };
    for(uint32_t y = 0; y < n; y++)
    {
        for(uint32_t x = 0; x < n; x++)
        {
            uint64_t v;
            cin >> v;
            A[y_transform(x, y)][x_transform(x, y)] = v;
        }
    }
    for(uint32_t y = 1; y <= MAX; y++) for(uint32_t x = 1; x <= MAX; x++)
        S[y][x] = S[y-1][x] + S[y][x-1] + A[y-1][x-1] - S[y-1][x-1];
    for(uint32_t i = 0; i < r; i++)
    {
        uint32_t cx, cy; int32_t k;
        cin >> cy >> cx >> k; cx--; cy--;
        int32_t x = x_transform(cx, cy), y = y_transform(cx, cy);
        cout << sum(S, x-k, y-k, x+k, y+k) << "\n";
        //cout << endl;
    }
}
