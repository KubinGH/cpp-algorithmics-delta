#include <iostream>
#include <array>
#include <cmath>
#define C(i, j) (C0[j] - C0[i] - (DS[j] - DS[i]) * WS[i])
#define R(i, j) (C(0, i) + C(i+1, j) + C(j+1, n))
#define UPDATE(_j) result = min(result, R(i, (_j)))

using namespace std;

const size_t MAX = 20000;

uint16_t n;
static array<uint32_t, MAX> W, D;
static array<uint32_t, MAX+1> WS, DS, C0;

uint32_t solve(uint16_t minpos1, uint16_t maxpos1, uint16_t minpos2, uint16_t maxpos2)
{
    if(minpos1 >= minpos2) minpos2 = minpos1 + 1;
    if(maxpos1 >= maxpos2) maxpos1 = maxpos2 - 1;
    if(minpos1 > maxpos1 or minpos2 > maxpos2) return -1;
    uint16_t j = (minpos2 + maxpos2) / 2,
             t = min(maxpos1, (uint16_t)(j - 1)) + 1, min_i = minpos1;
    uint32_t min_cost = R(minpos1, j);
    for(uint16_t i = minpos1; i < t; i++)
    {
        uint32_t cost = R(i, j);
        if(cost < min_cost)
        {
            min_i = i;
            min_cost = cost;
        }
    }
    return min(min(solve(minpos1, min_i, minpos2, (minpos2+maxpos2) / 2 - 1),
                   solve(min_i, maxpos1, (minpos2 + maxpos2) / 2 + 1, maxpos2)),
               min_cost);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for(uint16_t i = 0; i < n; i++)
    {
        cin >> W[i] >> D[i];
        if(i > 0) { WS[i+1] = WS[i]; DS[i+1] = DS[i]; C0[i+1] = C0[i]; }
        WS[i+1] += W[i]; DS[i+1] += D[i];
        C0[i+1] += WS[i+1] * D[i];
    }
    for(uint16_t i = 0; i < n - 1; i++)
        for(uint16_t j = i+1; j < n; j++)
            cout << i << ", " << j << ": " << R(i, j) << endl;
    cout << solve(0, n - 2, 1, n - 1) << endl;
}
