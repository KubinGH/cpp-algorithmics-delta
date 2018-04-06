#include <bits/stdc++.h>
#define clamp(n) ((n) < CLAMP_LO ? CLAMP_LO : ((n) > CLAMP_HI ? CLAMP_HI : (n)))

using namespace std;

const size_t MAX = 1100, FIX = 50, MAX_N = 1000;
const int32_t CLAMP_LO = FIX-1, CLAMP_HI = FIX+MAX_N;

static uint64_t A[MAX][MAX], S[MAX+1][MAX+1];

uint64_t sum_rect(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    x1 = clamp(x1); x2 = clamp(x2);
    y1 = clamp(y1); y2 = clamp(y2);
    //cerr << "sum_rect(" << x1+1-FIX << ", " << y1+1-FIX << ", " << x2+1-FIX << ", " << y2+1-FIX << ")" << endl;
    if(x1 == x2 and y1 == y2)
        return A[y1][x1];
    else
        return S[y2+1][x2+1] + S[y1][x1] - S[y2+1][x1] - S[y1][x2+1];
}

template<int32_t dx_sign, int32_t dy_sign>
uint64_t pyramid(int32_t x, int32_t y, int32_t k)
{
    //cerr << "pyramid<" << dx_sign << ", " << dy_sign <<  ">(" <<
    //        x+1-FIX << ", " << y+1-FIX << ", " << k << ")" << endl;
    if(k == 1)
        return sum_rect(x, y, x, y);
    else if(k == 2)
        return sum_rect(x, y, x, y)
               + sum_rect(x+dx_sign, y, x+dx_sign, y)
               + sum_rect(x, y+dy_sign, x, y+dy_sign);
    else
    {
        int32_t d = (k + 1) / 2 - 1;
        int32_t xc = x, yc = y;
        if(dx_sign == -1) xc -= d; else xc += d;
        if(dy_sign == -1) yc -= d; else yc += d;
        uint64_t r;
        if(dx_sign == -1 and dy_sign == -1)
            r = sum_rect(xc, yc, x, y);
        else if(dx_sign == -1)
            r = sum_rect(xc, y, x, yc);
        else if(dy_sign == -1)
            r = sum_rect(x, yc, xc, y);
        else
            r = sum_rect(x, y, xc, yc);
        return r + pyramid<dx_sign, dy_sign>(xc + dx_sign, y, k/2)
                 + pyramid<dx_sign, dy_sign>(x, yc + dy_sign, k/2);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cerr.setstate(ios::failbit);
    uint32_t n, r;
    cin >> n >> r;
    for(uint32_t y = 0; y < n; y++)
    {
        for(uint32_t x = 0; x < n; x++)
        {
            cin >> A[y+FIX][x+FIX];
            S[y+FIX+1][x+FIX+1] = A[y+FIX][x+FIX] + S[y+FIX][x+FIX+1]
                                + S[y+FIX+1][x+FIX] - S[y+FIX][x+FIX];
        }
    }
    for(uint32_t y = 0; y < MAX; y++)
        for(uint32_t x = 0; x < MAX; x++)
            if(not (x < FIX+n and y < FIX+n))
                S[y+1][x+1] = S[y][x+1] + S[y+1][x] - S[y][x];
    for(uint32_t ri = 0; ri < r; ri++)
    {
        int32_t x, y, k;
        cin >> y >> x >> k;
        x += FIX - 1; y += FIX - 1;
        //cerr << pyramid<1, 1>(x, y, k+1) << " " << pyramid<-1, 1>(x, y, k+1) << " "
        //     << pyramid<-1, -1>(x, y, k+1) << " " << pyramid<1, -1>(x, y, k+1) << endl;
        cout << pyramid<1, 1>(x, y, k+1) + pyramid<-1, 1>(x, y, k+1)
              + pyramid<-1, -1>(x, y, k+1) + pyramid<1, -1>(x, y, k+1)
              - sum_rect(x-k, y, x, y) - sum_rect(x, y-k, x, y)
              - sum_rect(x, y, x+k, y) - sum_rect(x, y, x, y+k)
              + A[y][x] << '\n';
    }
}
