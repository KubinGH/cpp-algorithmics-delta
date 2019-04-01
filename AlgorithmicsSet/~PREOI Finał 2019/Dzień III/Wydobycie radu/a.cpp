#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t h, w, q;
    cin >> h >> w >> q;
    vector<vector<uint32_t>> A(h, vector<uint32_t>(w));
    for(uint32_t y = 0; y < h; y++)
        for(uint32_t x = 0; x < w; x++)
            cin >> A[y][x];

    vector<uint32_t> row_max(h), col_max(w);

    for(uint32_t y = 0; y < h; y++)
        for(uint32_t x = 1; x < w; x++)
            if(A[y][x] > A[y][row_max[y]])
                row_max[y] = x;
    for(uint32_t x = 0; x < w; x++)
        for(uint32_t y = 1; y < h; y++)
            if(A[y][x] > A[col_max[x]][x])
                col_max[x] = y;

    auto special = [&](uint32_t y, uint32_t x) {
        return row_max[y] == x and col_max[x] == y;
    };

    uint32_t curr_count = 0;
    for(uint32_t y = 0; y < h; y++)
        for(uint32_t x = 0; x < w; x++)
            if(special(y, x))
                curr_count++;

    while(q --> 0)
    {
        uint32_t y, x, v;
        cin >> y >> x >> v; y--; x--;
        A[y][x] = v;
        if(not special(y, x))
        {
            if(A[y][x] > A[y][row_max[y]])
            {
                if(col_max[row_max[y]] == y)
                    curr_count--;
                row_max[y] = x;
            }
            if(A[y][x] > A[col_max[x]][x])
            {
                if(row_max[col_max[x]] == x)
                    curr_count--;
                col_max[x] = y;
            }
            if(special(y, x))
            {
                curr_count++;
            }
        }
        cout << curr_count << "\n";
    }
}
