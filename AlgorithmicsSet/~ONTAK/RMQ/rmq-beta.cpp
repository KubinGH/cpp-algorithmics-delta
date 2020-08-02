#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    vector<tuple<size_t, size_t, int>> queries;
    vector<pair<size_t, int>> events;
    vector<vector<pair<size_t, size_t>>> queries_by_value(n);
    while(q --> 0)
    {
        size_t l, r; int v;
        cin >> l >> r >> v;
        queries.emplace_back(l, r, v);
        events.emplace_back(  l, +v+1);
        events.emplace_back(r+1, -v-1);
        queries_by_value[v].emplace_back(l, r);
    }

    sort(events.rbegin(), events.rend());
    multiset<int> limits;
    vector<int> lo(n);
    vector<vector<size_t>> where_lo(n);
    for(size_t i = 0; i < n; i++)
    {
        while(not events.empty() and events.back().first == i)
        {
            auto x = events.back().second; events.pop_back();
            if(x > 0) limits.insert(x-1);
            else      limits.erase(limits.find(-x-1));
        }
        if(not limits.empty())
            lo[i] = *prev(limits.end());
        where_lo[lo[i]].push_back(i);
    }

    vector<pair<size_t, size_t>> where(n);
    for(size_t v = 0; v < n; v++)
    {
        size_t L = 0, R = n-1;
        for(auto lr : queries_by_value[v])
        {
            size_t l, r; tie(l, r) = lr;
            L = max(l, L);
            R = min(r, R);
            if(L > R)
            {
                cout << "-1" << endl;
                return 0;
            }
        }
        where[v] = {L, R};
    }

    set<size_t> available;
    vector<int> result(n, -1);
    for(size_t v = 0; v < n; v++)
    {
        for(auto i : where_lo[v])
            available.insert(i);
        auto it = available.lower_bound(where[v].first);
        if(it == available.end() or where[v].second < *it)
        {
            cout << "-1" << endl;
            return 0;
        }
        result[*it] = v;
        available.erase(it);
    }

    for(size_t i = 0; i < n; i++)
        cout << result[i] << ' ';
    cout << endl;
}
