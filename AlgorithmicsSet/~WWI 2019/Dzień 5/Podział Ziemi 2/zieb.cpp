#include <bits/stdc++.h>

using namespace std;

template<typename T>
vector<vector<T>> partials_2d(const vector<vector<T>>& a)
{
    const size_t h = a.size(), w = a[0].size();
    vector<vector<T>> s(h+1, vector<T>(w+1));
    for(size_t y = 0; y < h; y++)
        for(size_t x = 0; x < w; x++)
            s[y+1][x+1] = a[y][x] + s[y][x+1] + s[y+1][x] - s[y][x];
    return s;
}

template<typename T>
T psum(const vector<vector<T>>& s, size_t x1, size_t y1, size_t x2, size_t y2)
{
    return s[y2][x2] + s[y1][x1] - s[y2][x1] - s[y1][x2];
}

string quotient_fmt3(uint64_t a, uint64_t b)
{
    uint64_t c = (a * 1000) / b;
    auto i = to_string(c / 1000), f = to_string(c % 1000);
    while(f.size() < 3)
        f = '0' + f;
    return i + "." + f;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t w, h, k; uint64_t b;
    cin >> w >> h >> k >> b;

    vector<vector<uint64_t>> a(h, vector<uint64_t>(w)), e(h, vector<uint64_t>(w));

    for(size_t y = 0; y < h; y++)
        for(size_t x = 0; x < w; x++)
            cin >> a[y][x], e[y][x] = (a[y][x] % b != 0);

    auto s = partials_2d(a);
    auto d = partials_2d(e);

    size_t rx1 = 0, ry1 = 0, rx2 = 0, ry2 = 0;

    for(size_t x1 = 0; x1 < w; x1++)
        for(size_t y1 = 0; y1 < h; y1++)
            for(size_t x2 = x1+1; x2 <= w; x2++)
                for(size_t y2 = y1+1; y2 <= h; y2++)
    {
        bool ok = false;
        if(psum(d, x1, y1, x2, y2) <= k)
        {
            if((x2-x1)*(y2-y1) > (rx2-rx1)*(ry2-ry1))
                ok = true;
            else if((x2-x1)*(y2-y1) == (rx2-rx1)*(ry2-ry1))
            {
                if(psum(s, x1, y1, x2, y2) > psum(s, rx1, ry1, rx2, ry2))
                    ok = true;
                else if(psum(s, x1, y1, x2, y2) == psum(s, rx1, ry1, rx2, ry2))
                {
                    if(tie(x1, y1, x2, y2) < tie(rx1, ry1, rx2, ry2))
                        ok = true;
                }
            }
            if(ok)
                rx1 = x1, ry1 = y1, rx2 = x2, ry2 = y2;
        }
    }

    if((rx2-rx1)*(ry2-ry1) == 0)
        cout << "NYET";
    else
    {
        cout << (rx2-rx1)*(ry2-ry1) << " " << (rx2-rx1) << " " << (ry2-ry1) << " ";
        cout << fixed << setprecision(3) << quotient_fmt3(psum(s, rx1, ry1, rx2, ry2), (rx2-rx1)*(ry2-ry1)) << '\n';
        for(size_t y = ry1; y < ry2; y++, cout << '\n')
            for(size_t x = rx1; x < rx2; x++, cout << " ")
                cout << a[y][x];
    }
}
