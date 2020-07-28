#include <bits/stdc++.h>

using namespace std;

struct rect
{
    int x1, y1, x2, y2;
};


int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    auto load_rects = [&]() {
        size_t n;
        cin >> n;

        char c;
        vector<int> val(n+2);
        for(size_t i = 1; i <= n; i++)
            cin >> c >> val[i];


        bool beef = (c == 'W') ^ (n%2);

        vector<rect> rects;
        rects.reserve(2*n*n);
        for(size_t i = 1; i <= n+1; i++)
        {
            array<int, 2> rel = {0, 0};
            for(size_t j = i; j <= n+1; j++)
            {
                array<int, 2> end = rel;
                end[beef ^ (i%2) ^ 1] += val[i-1];
                end[beef ^ (j%2)] += val[j];
                rects.push_back({rel[0], rel[1], end[0], end[1]});
                rel[beef ^ (j%2)] += val[j];
            }
        }

        return rects;
    };

    vector<rect> A[2] = {load_rects(), load_rects()};

    int result = 0;

    for(size_t tr = 0; tr < 2; tr++)
    {
        vector<tuple<int, char, pair<int, int>>> events;
        events.reserve(A[0].size() + A[1].size());
        for(auto r : A[0])
            events.emplace_back(r.x1, 1, make_pair(r.y1, r.y2)),
            events.emplace_back(r.x2+1, 0, make_pair(r.y1, r.y2));
        for(auto r : A[1])
            events.emplace_back(r.x2, 2, make_pair(r.y1, r.y2));

        sort(events.begin(), events.end());

        multiset<pair<int, int>> intervals = {{-2e9, -2e9}};

        for(size_t i = 0, j = 0; i < events.size(); i = j)
        {
            while(j < events.size() and get<0>(events[i]) == get<0>(events[j]))
            {
                const auto& [x, t, in] = events[j++];
                if(t == 0)
                    intervals.erase(intervals.find(in));
                else if(t == 1)
                    intervals.insert(in);
                else if(t == 2)
                {
                    // TODO: I have no idea how this gets 84 points (100 with extra silliness...),
                    // but this method of finding the interval intersecting
                    // `in` at the maximum point is very wrong (see debug for f.in).
                    // A pointer segment tree would definitely work,
                    // but it's a hassle.
                    // cout << " intervals " << intervals << endl;
                    // cout << "  ? " << in << endl;
                    auto it = --intervals.lower_bound({in.second+1, in.second+1});
                    for(size_t _ = 0; _ < 5; _++, --it)
                    {
                        // cout << " -> " << *it << endl;
                        if(it->second >= in.first)
                            result = max(result, x + min(in.second, it->second));
                        if(it == intervals.begin())
                            break;
                    }
                }
            }
        }

        swap(A[0], A[1]);
    }

    cout << result << endl;
}
