#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500000;

struct point_t { uint32_t x, y; };
typedef pair<point_t, point_t> point_pair;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<point_pair, MAX> B;
    static array<uint32_t, MAX> cols, rows;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        for(uint32_t p = x1; p <= x2; p++)
            cols[p]++;
        for(uint32_t p = y1; p <= y2; p++)
            rows[p]++;
        B.first.x = x1; B.first.y = y1;
        B.second.x = x2; B.second.y = y2;
    }
    static array<point_t, MAX> R;

}
