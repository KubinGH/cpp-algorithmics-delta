#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC march ("tune=native")

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t h, w;
    cin >> h >> w;

    static int a[1024][1024];

    for(size_t y = 0; y < h; y++)
        for(size_t x = 0; x < w; x++)
            cin >> a[y][x];

    stack<tuple<size_t, size_t, size_t, size_t, char>> queries;

    size_t q;
    cin >> q;
    while(q --> 0)
    {
        size_t y1, y2, x1, x2; char t;
        cin >> y1 >> y2 >> x1 >> x2 >> t; x1--; x2--; y1--; y2--;
        queries.emplace(y1, y2, x1, x2, t);
    }

    while(not queries.empty())
    {
        size_t y1, y2, x1, x2; char t;
        tie(y1, y2, x1, x2, t) = queries.top(); queries.pop();
        if(t == '-')
        {
            for(size_t y = y1; y < (y1+y2+1)/2; y++)
                for(size_t x = x1; x <= x2; x++)
                    swap(a[y][x], a[y1+y2-y][x]);
        }
        else if(t == '|')
        {
            for(size_t x = x1; x < (x1+x2+1)/2; x++)
                for(size_t y = y1; y <= y2; y++)
                    swap(a[y][x], a[y][x1+x2-x]);
        }
    }

    for(size_t y = 0; y < h; y++, cout << '\n')
        for(size_t x = 0; x < w; x++, cout << " ")
            cout << a[y][x];
}
