#include <bits/stdc++.h>

using namespace std;

int main()
{
#ifndef XHOVA
    ifstream cin("buckets.in");
    ofstream cout("buckets.out");
#endif
    string L[10];
    for(uint32_t i = 0; i < 10; i++)
        cin >> L[i];

    uint32_t sx = -1u, sy = -1u, gx = -1u, gy = -1u;
    for(uint32_t y = 0; y < 10; y++)
        for(uint32_t x = 0; x < 10; x++)
    {
        if(L[y][x] == 'L')
            sx = x, sy = y;
        else if(L[y][x] == 'B')
            gx = x, gy = y;
    }

    uint32_t D[10][10];
    for(uint32_t y = 0; y < 10; y++)
        for(uint32_t x = 0; x < 10; x++)
            D[y][x] = -1u;
    D[sy][sx] = 0;

    queue<pair<uint32_t, uint32_t>> Q;
    Q.emplace(sx, sy);
    while(not Q.empty())
    {
        auto p = Q.front(); Q.pop();
        uint32_t x, y;
        tie(x, y) = p;
        if(L[y][x] == 'R')
            continue;
        if(x - 1 < 10 and D[y][x-1] == -1u)
            D[y][x-1] = D[y][x] + 1, Q.emplace(x-1, y);
        if(x + 1 < 10 and D[y][x+1] == -1u)
            D[y][x+1] = D[y][x] + 1, Q.emplace(x+1, y);
        if(y - 1 < 10 and D[y-1][x] == -1u)
            D[y-1][x] = D[y][x] + 1, Q.emplace(x, y-1);
        if(y + 1 < 10 and D[y+1][x] == -1u)
            D[y+1][x] = D[y][x] + 1, Q.emplace(x, y+1);
    }

    cout << D[gy][gx] - 1;
}
