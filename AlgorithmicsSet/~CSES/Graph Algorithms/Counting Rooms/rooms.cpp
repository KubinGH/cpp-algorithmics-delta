#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t h, w;
    cin >> h >> w;

    const size_t n = (w+2)*(h+2);
    vector<bool> open(n);
    for(size_t y = 0; y < h; y++)
    {
        string row;
        cin >> row;
        for(size_t x = 0; x < w; x++)
            open[(y+1)*(w+2)+x+1] = row[x] == '.';
    }

    size_t result = 0;
    for(size_t s = 0; s < n; s++) if(open[s])
    {
        vector<size_t> stk = {s};
        auto maybe = [&](size_t v) {
            if(open[v])
                open[v] = false, stk.push_back(v);
        };
        while(not stk.empty())
        {
            auto u = stk.back(); stk.pop_back();
            maybe(u - 1); maybe(u + 1);
            maybe(u - (w+2)); maybe(u + (w+2));
        }
        result++;
    }

    cout << result << endl;
}
