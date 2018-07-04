#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 128;

template<typename T>
T max(T a, T b, T c) { return max(max(a, b), c); }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t h, w;
    cin >> h >> w;
    static uint32_t A[MAX][MAX];
    uint32_t n = 2*max(w, h)-1;
    for(uint32_t y = 0; y < h; y++)
        for(uint32_t x = 0; x < w; x++)
            cin >> A[x+max(w,h)-1-y][x+y];
    for(uint32_t y = 0; y < n; y++)
        for(uint32_t x = 0; x < n; x++)
            cout << A[x][y] << " \n"[x==n-1];
}
