#include <bits/stdc++.h>
#define clamp(n) ((n) < CLAMP_LO ? CLAMP_LO : ((n) > CLAMP_HI ? CLAMP_HI : (n)))
#define unlocked_sum(x1, y1, x2, y2) (S[y2+1][x2+1] + S[y1][x1] - S[y2+1][x1] - S[y1][x2+1])

using namespace std;

const size_t MAX = 1100, FIX = 50, MAX_N = 1000, MAX_P = 8;
const int32_t CLAMP_LO = FIX-1, CLAMP_HI = FIX+MAX_N;
const int32_t SMAX = MAX, SFIX = FIX;

static uint64_t A[MAX][MAX], S[MAX+1][MAX+1], P[MAX][MAX][MAX_P/2][4];

uint32_t log2floor(uint32_t n)
{
    return 31 - __builtin_clz(n);
}

uint64_t sum(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    if(x1 > x2) swap(x1, x2);
    if(y1 > y2) swap(y1, y2);
    x1 = clamp(x1); x2 = clamp(x2);
    y1 = clamp(y1); y2 = clamp(y2);
    //cerr << "sum(" << x1 << ", " << y1 << ", " << x2 << ", " << y2 << ")" << endl;
    if(x1 == x2 and y1 == y2)
        return A[y1][x1];
    else
        return unlocked_sum(x1, y1, x2, y2);
}

template<int32_t dx_sign, int32_t dy_sign>
uint64_t pyramid_pow2(int32_t x, int32_t y, int32_t p)
{
    int32_t s;
    if(dx_sign == 1 and dy_sign == 1)
        s = 0;
    else if(dx_sign == -1 and dy_sign == 1)
        s = 1;
    else if(dx_sign == -1 and dy_sign == -1)
        s = 2;
    else if(dx_sign == 1 and dy_sign == -1)
        s = 3;
    if(p < (int32_t)MAX_P/2)
        return P[y][x][p][s];
    uint64_t k = 1llu << p;
    uint64_t r = sum(x, y, x+(k/2-1)*dx_sign, y+(k/2-1)*dy_sign);
    if(0 <= x+(k/2)*dx_sign and x+(k/2)*dx_sign < SMAX)
        r += pyramid_pow2<dx_sign, dy_sign>(x+(k/2)*dx_sign, y, p-1);
    if(0 <= y+(k/2)*dy_sign and y+(k/2)*dy_sign < SMAX)
        r += pyramid_pow2<dx_sign, dy_sign>(x, y+(k/2)*dy_sign, p-1);
    return r;
}

template<int32_t dx_sign, int32_t dy_sign>
uint64_t pyramid(int32_t x, int32_t y, int32_t k)
{
    uint64_t r = 0;
    while(k and 0 <= x and x < SMAX and 0 <= y and y < SMAX)
    {
        int32_t d = 1 << log2floor(k);
        int32_t px = x+(k-d)*dx_sign;
        if(0 <= px and px <= SMAX)
            r += pyramid_pow2<dx_sign, dy_sign>(px, y, log2floor(k));
        if(k - d > 0)
            r += sum(x, y, x + (k-d-1)*dx_sign, y + (d-1)*dy_sign);
        k -= d;
        y += d * dy_sign;
    }
    return r;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    //cerr.setstate(ios::failbit);
    uint32_t n, r;
    cin >> n >> r;
    for(uint32_t y = FIX; y < FIX + n; y++)
        for(uint32_t x = FIX; x < FIX + n; x++)
            cin >> A[y][x];
    for(uint32_t y = 0; y < MAX; y++) for(uint32_t x = 0; x < MAX; x++)
    {
        S[y+1][x+1] = A[y][x] + S[y][x+1] + S[y+1][x] - S[y][x];
        P[y][x][0][0] = P[y][x][0][1] =
            P[y][x][0][2] = P[y][x][0][3] = A[y][x];
    }
    for(int32_t p = 1, k = 2; k <= (int32_t)n and p < (int32_t)MAX_P/2; p++, k *= 2)
    {
        for(int32_t y = SFIX; y < SFIX+(int32_t)n; y++)
            for(int32_t x = SFIX; x < SFIX+(int32_t)n; x++)
        {
            auto create = [&](int32_t sx, int32_t sy, int32_t s)
            {
                P[y][x][p][s] += sum(x, y, x+(k/2-1)*sx, y+(k/2-1)*sy);
                if(0 <= x+(k/2)*sx and x+(k/2)*sx < SMAX)
                    P[y][x][p][s] += P[y][x+(k/2)*sx][p-1][s];
                if(0 <= y+(k/2)*sy and y+(k/2)*sy < SMAX)
                    P[y][x][p][s] += P[y+(k/2)*sy][x][p-1][s];
            };
            create(1, 1, 0);
            create(-1, 1, 1);
            create(-1, -1, 2);
            create(1, -1, 3);
        }
    }
    for(uint32_t ri = 0; ri < r; ri++)
    {
        int32_t x, y, k;
        cin >> y >> x >> k;
        x += SFIX - 1; y += SFIX - 1;
        cout << pyramid<1, 1>(x, y, k+1) + pyramid<-1, 1>(x, y, k+1)
              + pyramid<-1, -1>(x, y, k+1) + pyramid<1, -1>(x, y, k+1)
              - A[y][x]
              - unlocked_sum(clamp(x-k), y, clamp(x+k), y)
              - unlocked_sum(x, clamp(y-k), x, clamp(y+k)) << '\n';
    }
}

/*
8 0
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
*/
