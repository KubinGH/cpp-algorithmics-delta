#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1024;

bool is_peak(uint32_t A[MAX][MAX], uint32_t m, uint32_t x, uint32_t y)
{
    uint32_t a = A[y][x]%m;
    return a >= A[y][x-1]%m and a >= A[y][x+1]%m
       and a >= A[y-1][x]%m and a >= A[y+1][x]%m;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static uint32_t A[MAX][MAX], B[MAX][MAX];
    static pair<uint32_t, uint32_t> L[8];
    uint32_t li = 0; uint32_t lf = 0;
    for(uint32_t y = 0; y < n; y++)
    {
        for(uint32_t x = 0; x < n; x++)
        {
            cin >> A[y+1][x+1];
            B[x+1][y+1] = A[y+1][x+1];
        }
    }
    uint32_t q;
    cin >> q;
    for(uint32_t i = 0; i < q; i++)
    {
        uint32_t m;
        cin >> m;
        uint32_t rx = 0, ry = 0;
        uint32_t x1 = 1, y1 = 1, x2 = n, y2 = n;
        uint32_t w = x2-x1+1, h = y2-y1+1;
        if(lf == 8)
        {
            for(uint32_t l = 0; l < 8; l++)
            {
                if(is_peak(A, m, L[l].first, L[l].second))
                {
                    tie(rx, ry) = L[l];
                    goto after;
                }
            }
        }
        while(w > 2)
        {
            if(true or w > h) // columns
            {
                uint32_t mx = (x1+x2)/2;
                uint32_t amax = B[mx][y1]%m; uint32_t imax_y = y1;
                for(uint32_t y = y1+1; y <= y2; y++)
                {
                    uint32_t a = B[mx][y]%m;
                    if(a > amax)
                    {
                        amax = a;
                        imax_y = y;
                    }
                }
                //cout << amax << endl;
                if(amax >= A[imax_y][mx-1]%m and
                   amax >= A[imax_y][mx+1]%m)
                {
                    rx = mx; ry = imax_y;
                    goto after;
                }
                else if(amax < A[imax_y][mx-1]%m)
                    x2 = mx;
                else
                    x1 = mx;
                w = x2-x1+1;
            }
            else if(false) // rows
            {
                uint32_t my = (y1+y2)/2;
                uint32_t amax = -1u; uint32_t imax_x = x1;
                for(uint32_t x = x1; x <= x2; x++)
                {
                    uint32_t a = A[my][x]%m;
                    if(amax == -1u or a > amax)
                    {
                        amax = a;
                        imax_x = x;
                    }
                }
                if(amax >= B[imax_x][my-1]%m and
                   amax >= B[imax_x][my+1]%m)
                {
                    rx = imax_x; ry = my;
                    goto after;
                }
                else if(amax < B[imax_x][my-1]%m)
                    y2 = my;
                else
                    y1 = my;
                h = y2-y1+1;
            }
        }
        for(uint32_t y = y1; y <= y2; y++) for(uint32_t x = x1; x <= x2; x++)
        {
            uint32_t a = A[y][x]%m;
            if(a >= A[y][x-1]%m and a >= A[y][x+1]%m
           and a >= A[y-1][x]%m and a >= A[y+1][x]%m)
            {
                rx = x; ry = y;
                goto after;
            }
        }
    after:;
        cout << ry-1 << " " << rx-1 << "\n";
        if(lf < 8)
            L[lf].first = rx, L[lf].second = ry, lf++;
        else
        {
            L[li].first = rx, L[li].second = ry;
            li++; li %= 8;
        }
    }
}
