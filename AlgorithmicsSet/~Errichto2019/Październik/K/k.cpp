#include <algorithm>
#include <iostream>
#include <optional>
#include <numeric>
#include <vector>

using namespace std;

struct tile { size_t x, y; };

optional<vector<pair<size_t, size_t>>> make_comb(int w, int h)
{
    vector<pair<size_t, size_t>> result;
    if(w*h % 2) return {};
    else if(w % 2)
    {
        auto comb = make_comb(h, w);
        for(auto [x, y] : *comb)
            result.emplace_back(y, x);
    }
    else
    {
        int x = 0, y = 0, ydir = 1;
        result.emplace_back(x, y);
        while(x < w-1)
        {
            while(0 < y + ydir and y + ydir < h)
                result.emplace_back(x, y += ydir);
            ydir = -ydir;
            result.emplace_back(++x, y);
        }
        while(y)
            result.emplace_back(x, --y);
        while(x > 1)
            result.emplace_back(--x, y);
    }
    return result;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t h, w;
    cin >> h >> w;

    int sum = 0;
    vector<vector<int>> A(h, vector<int>(w));
    for(auto& row : A)
        for(auto& val : row)
            cin >> val, sum += val;

    if(auto comb = make_comb(w, h); sum >= 0 and comb)
    {
        vector<int> a, s = {0};
        for(auto p : *comb)
            a.push_back(A[p.second][p.first]);
        partial_sum(a.begin(), a.end(), back_inserter(s));
        auto shift = min_element(s.begin(), s.end()) - s.begin();
        rotate(comb->begin(), comb->begin() + shift, comb->end());

        for(auto p : *comb)
            cout << p.second+1 << ' ' << p.first+1 << '\n';
    }
    else
        cout << -1;
}
