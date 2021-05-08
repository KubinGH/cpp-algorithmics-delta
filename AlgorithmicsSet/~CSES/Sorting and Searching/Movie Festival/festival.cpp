#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<pair<size_t, size_t>> begin_end(n);
    for(auto& [a, b] : begin_end)
        cin >> a >> b;
    sort(begin_end.begin(), begin_end.end());

    set<pair<size_t, size_t>> end_index_set;
    for(size_t i = 0; i < n; i++)
        end_index_set.emplace(begin_end[i].second, i);

    size_t r = 0, c = 0;
    while(c < n)
    {
        auto [b, i] = *end_index_set.begin();
        end_index_set.erase(end_index_set.begin());
        while(c < n and begin_end[c].first < b)
            end_index_set.erase({begin_end[c].second, c}), c++;
        r++;
    }

    cout << r << endl;
}
