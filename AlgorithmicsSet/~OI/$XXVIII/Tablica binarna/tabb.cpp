// Jakub Bachurski
// Tablica binarna - O(q 2^nm)

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, q;
    cin >> n >> m >> q;

    assert(n*m < 32);

    vector<vector<int8_t>> A(n, vector<int8_t>(m));
    auto xorr = [&](size_t y, size_t x) {
        if(y < n and x < m)
            A[y][x] ^= 1;
    };
    auto xorect = [&](size_t y1, size_t x1, size_t y2, size_t x2) {
        xorr(y1, x1); xorr(y2, x1); xorr(y1, x2); xorr(y2, x2);
    };
    auto solve = [&]() {
        int result = INT_MAX;
        for(size_t mask = 0; mask < (1u << (n*m)); mask++)
        {
            if(__builtin_popcount(mask) > result)
                continue;
            for(size_t re : {0, 1})
            {
                for(size_t y = 0; y < n; y++)
                  for(size_t x = 0; x < m; x++)
                    if(mask >> (y*m + x) & 1)
                      xorect(0, 0, y+1, x+1);
                if(not re)
                {
                    bool ok = true;
                    for(size_t y = 0; y < n; y++)
                        for(size_t x = 0; x < m; x++)
                            if(A[y][x])
                                ok = false;
                    if(ok)
                        result = min(result, __builtin_popcount(mask));
                }
            }
        }
        return result;
    };

    while(q --> 0)
    {
        size_t y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2; y1--; x1--;
        xorect(y1, x1, y2, x2);
        cout << solve() << '\n';
    }
}
