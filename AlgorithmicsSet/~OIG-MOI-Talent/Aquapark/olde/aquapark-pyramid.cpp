#include <bits/stdc++.h>
#define clamp(n) ((n) < CLAMP_LO ? CLAMP_LO : ((n) > CLAMP_HI ? CLAMP_HI : (n)))
#define unlocked_sum(x1, y1, x2, y2) (S[y2+1][x2+1] + S[y1][x1] - S[y2+1][x1] - S[y1][x2+1])

using namespace std;

const size_t MAX = 1100, FIX = 50, MAX_N = 1000;
const int32_t CLAMP_LO = FIX-1;
int32_t CLAMP_HI = FIX+MAX_N;

static uint64_t A[MAX][MAX], S[MAX+1][MAX+1], R[MAX][MAX+1];

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
uint32_t sum_row(int32_t x1, int32_t x2, int32_t y)
{
    if(x1 > x2) swap(x1, x2);
    x1 = clamp(x1); x2 = clamp(x2); y = clamp(y);
    return unlocked_sum(x1, y, x2, y);
    return R[y][x2+1] - R[y][x1];
}

template<int32_t dx_sign, int32_t dy_sign>
uint64_t pyramid(int32_t x, int32_t y, int32_t k)
{
    //cerr << "pyramid<" << dx_sign << ", " << dy_sign <<  ">(" <<
    //        x+1-FIX << ", " << y+1-FIX << ", " << k << ")" << endl;
    if(x < CLAMP_LO or x > CLAMP_HI or y < CLAMP_LO or y > CLAMP_HI)
        return 0;
    if(k == 1)
        return A[y][x];
    else if(k == 2)
        return A[y][x] + A[y+dy_sign][x] + A[y][x+dx_sign];
    else if(k <= 64)
    {
        uint32_t s = 0;
        for(int32_t dx = k-1, dy = 0; dx >= 0 and dy < k; dx--, dy++)
            s += sum_row(x, x + dx*dx_sign, y + dy*dy_sign);
        return s;
    }
    else
    {
        int32_t d = (k + 1) / 2 - 1;
        int32_t xc = x + d * dx_sign, yc = y + d * dy_sign;
        return sum(x, y, xc, yc)
             + pyramid<dx_sign, dy_sign>(xc + dx_sign, y, k/2)
             + pyramid<dx_sign, dy_sign>(x, yc + dy_sign, k/2);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, r;
    cin >> n >> r;
    CLAMP_HI = CLAMP_LO + n + 2;
    for(uint32_t y = FIX; y < FIX + n; y++)
    {
        for(uint32_t x = FIX; x < FIX + n; x++)
        {
            cin >> A[y][x];
        }
    }
    for(uint32_t y = CLAMP_LO; y <= CLAMP_HI; y++)
        for(uint32_t x = CLAMP_LO; x <= CLAMP_HI; x++)
    {
        S[y+1][x+1] = A[y][x] + S[y][x+1] + S[y+1][x] - S[y][x];
        R[y][x+1] = R[y][x] + A[y][x];
    }
    while(r)
    {
        int32_t x, y, k;
        cin >> y >> x >> k;
        x += FIX - 1; y += FIX - 1;
        //cerr << pyramid<1, 1>(x, y, k+1) << " " << pyramid<-1, 1>(x, y, k+1) << " "
        //     << pyramid<-1, -1>(x, y, k+1) << " " << pyramid<1, -1>(x, y, k+1) << endl;
        cout << pyramid<1, 1>(x, y, k+1) + pyramid<-1, 1>(x, y, k+1)
              + pyramid<-1, -1>(x, y, k+1) + pyramid<1, -1>(x, y, k+1)
              - A[y][x]
              - unlocked_sum(clamp(x-k), y, clamp(x+k), y)
              - unlocked_sum(x, clamp(y-k), x, clamp(y+k)) << '\n';
        r--;
    }
}
