#include <bits/stdc++.h>

using namespace std;

struct rect_t { uint32_t x1, y1, x2, y2; };

istream& operator>> (istream& in, rect_t& r)
{
    return in >> r.x1 >> r.y1 >> r.x2 >> r.y2;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    uint32_t n, k, l;
    cin >> n >> k >> l;

    vector<rect_t> rects(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> rects[i];

    uint64_t result = 0;

    for(uint32_t i = 0; i < k; i++)
    {
        uint32_t x;
        cin >> x;
        for(auto r : rects)
            if(r.x1 <= x and x <= r.x2)
                result++;
    }
    for(uint32_t i = 0; i < l; i++)
    {
        uint32_t y;
        cin >> y;
        for(auto r : rects)
            if(r.y1 <= y and y <= r.y2)
                result++;
    }
    cout << result;
}
