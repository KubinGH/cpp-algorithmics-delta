// Calculation of count of rectangles of given size in bit matrix
// such that no 0 is contained. The function expects 0-margins around
// the edges of the matrix.
// Complexity: linear in size of grid
// Last revision: February 2020

#pragma once

#include <vector>
#include <cstddef>

using std::vector;
using std::size_t;

vector<vector<uint>> get_rect_count(const vector<vector<bool>>& A)
{
    const size_t m = A[0].size() - 2, n = A.size() - 2;
    vector<vector<uint>> R(n+2, vector<uint>(m+2)), D = R;

    for(size_t y = 1; y <= n; y++)
        for(size_t x = 1; x <= m; x++)
            D[y][x] = A[y][x] ? D[y-1][x] + 1 : 0;

    for(size_t y = 1; y <= n; y++)
    {
        struct rect { uint w, h; };
        vector<rect> S = {{0, 0}};

        for(size_t x = 1; x <= m+1; x++)
        {
            auto d = D[y][x];
            uint e = 0;
            while(S.size() > 1 and S.back().h >= d)
            {
                auto [w, h] = S.back(); S.pop_back();
                auto l = max(S.back().h, d);
                e += w;
                R[l + 1][e]++;
                R[h + 1][e]--;
            }
            S.push_back({++e, d});
        }
    }

    for(size_t y = 0; y <= n; y++)
        for(size_t x = 0; x <= m; x++)
            R[y+1][x] += R[y][x];
    for(size_t t = 0; t < 2; t++)
        for(size_t y = 0; y <= n+1; y++)
            for(size_t x = m+2; x --> 1; )
                R[y][x-1] += R[y][x];

    return R;
}

