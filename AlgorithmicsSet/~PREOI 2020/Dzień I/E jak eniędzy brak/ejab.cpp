#include <bits/stdc++.h>

using namespace std;

int main()
{
    size_t t;
    cin >> t;

    while(t --> 0)
    {
        size_t n;
        cin >> n;

        vector<tuple<int, int, int>> P(n);
        for(auto& [x, y, w] : P)
            cin >> x >> y >> w;

        int64_t opt = 0;

        for(size_t tr = 0; tr < 2; tr++)
        {
            for(auto [x1, y1, w1] : P)
                for(auto [x2, y2, w2] : P)
            {
                int64_t c = 0;
                for(auto [x, y, w]: P)
                    if(x1 <= x and x <= x2 and y1 <= y and y <= y2)
                        c += w;
                opt = max(opt, c);
            }

            for(auto& [x, y, w] : P)
                x = -x;
        }


        cout << opt << '\n';
    }
}
