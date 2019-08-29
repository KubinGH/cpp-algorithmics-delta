#include <bits/stdc++.h>
#include <ext/rope>

using namespace std;
using namespace __gnu_cxx;

void swap_segments(rope<int>& R, size_t a, size_t b, size_t x, size_t y)
{
    auto seg1 = R.substr(a, b - a + 1);
    auto seg2 = R.substr(x, y - x + 1);
    R.erase(x, y - x + 1);
    R.erase(a, b - a + 1);
    R.insert(a, seg2);
    R.insert(x, seg1);
}

void reverse_segment(rope<int>& R, size_t a, size_t b)
{
    const size_t n = R.size() / 2;
    uint32_t x = 2*n - b - 1, y = 2*n - a - 1;
    swap_segments(R, a, b, x, y);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t h, w;
    cin >> h >> w;

    rope<int> r[1024];

    for(size_t y = 0; y < h; y++)
    {
        vector<int> v;
        for(size_t x = 0; x < w; x++)
        {
            int c;
            cin >> c;
            v.push_back(c);
            r[y].push_back(c);
        }
        for(size_t x = w; x --> 0; )
            r[y].push_back(v[x]);
    }

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
            reverse(r + y1, r + y2+1);
        else if(t == '|')
        {
            for(size_t y = y1; y <= y2; y++)
                reverse_segment(r[y], x1, x2);
        }
    }

    for(size_t y = 0; y < h; y++, cout << '\n')
    {
        size_t i = 0;
        for(auto it = r[y].begin(); i < w; ++it, i++)
            cout << *it << " ";
    }
}
