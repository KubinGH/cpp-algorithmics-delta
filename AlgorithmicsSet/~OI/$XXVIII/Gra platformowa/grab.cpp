// Jakub Bachurski
// Gra platformowa - O(qnd)

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, d; size_t z;
    cin >> n >> d >> z;

    int h = 0;
    set<pair<int, int>> holes;
    for(int y = 1; y <= n; y++)
    {
        size_t k;
        cin >> k;
        for(size_t i = 0; i < k; i++)
        {
            size_t x;
            cin >> x;
            holes.emplace(x, y);
            h++;
        }
    }

    while(z --> 0)
    {
        int s;
        cin >> s;

        map<pair<int, int>, int> dist;
        deque<pair<int, int>> que;

        auto vi = [&](int x, int y, int r, bool w) {
            auto p = make_pair(x, y);
            if(not dist.count(p) or r + w < dist[p])
            {
                dist[p] = r + w;
                if(w)  que.emplace_back (x, y);
                else   que.emplace_front(x, y);
            }
        };

        que.emplace_front(1, s);
        while(not que.empty())
        {
            auto [x, y] = que.front(); que.pop_front();
            auto r = dist[{x, y}];
            if(x == d)
            {
                cout << r << '\n';
                break;
            }

            if(holes.count(pair<int, int>{x+1, y}))
            {
                vi(x + 2, y, r, 1);
                if(y < n)
                    vi(x + 1, y + 1, r, 0);
            }
            else
                vi(x + 1, y, r, 0);

            if(y > 1 and holes.count(pair<int, int>{x, y-1}))
                vi(x + 1, y - 1, r, 1);
        }
    }
}
