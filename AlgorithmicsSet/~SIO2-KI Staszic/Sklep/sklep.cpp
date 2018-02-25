#include <bits/stdc++.h>
#define C(x, y) ((y)*w+(x))
#define X(c) ((c) % w)
#define Y(c) ((c) / w)

using namespace std;

const size_t MAX = 1000000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t h, w;
    cin >> h >> w;
    static array<bool, MAX> A;
    uint32_t start = 0, goal = 0;
    for(uint32_t y = 0; y < h; y++)
    {
        for(uint32_t x = 0; x < w; x++)
        {
            char c;
            cin >> c;
            if(c == 'W')
                start = C(x, y);
            else if(c == 'T')
                goal = C(x, y);
            else if(c == 'R')
                A[C(x, y)] = true;
        }
    }
    queue<pair<uint32_t, uint32_t>> Q;
    Q.emplace(start, 0);
    A[start] = true;
    while(not Q.empty())
    {
        uint32_t c = Q.front().first, d = Q.front().second;
        if(c == goal)
        {
            cout << d;
            return 0;
        }
        uint32_t cx = X(c), cy = Y(c); Q.pop();
        if(cy > 0 and not A[C(cx, cy-1)])
        {
            A[C(cx, cy-1)] = true;
            Q.emplace(C(cx, cy-1), d + 1);
        }
        if(cy < h - 1 and not A[C(cx, cy+1)])
        {
            A[C(cx, cy+1)] = true;
            Q.emplace(C(cx, cy+1), d + 1);
        }
        if(cx > 0 and not A[C(cx-1, cy)])
        {
            A[C(cx-1, cy)] = true;
            Q.emplace(C(cx-1, cy), d + 1);
        }
        if(cx < w - 1 and not A[C(cx+1, cy)])
        {
            A[C(cx+1, cy)] = true;
            Q.emplace(C(cx+1, cy), d + 1);
        }
    }
    cout << '0';
}
