#include <bits/stdc++.h>

using namespace std;

template<typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    size_t n, m;
    cin >> n >> m;

    vector<min_priority_queue<uint64_t>> today(n);
    min_priority_queue<pair<uint64_t, size_t>> summary;

    for(size_t i = 0; i < n; i++)
    {
        vector<uint64_t> costs(m);
        for(auto& a : costs)
            cin >> a;
        sort(costs.begin(), costs.end());
        for(size_t j = 0; j < m; j++)
            today[i].push(costs[j] + 2*j + 1);
    }

    uint64_t result = 0;
    for(size_t k = 0; k < n; k++)
    {
        summary.emplace(today[k].top(), k);
        auto [_, i] = summary.top();
        summary.pop();
        result += today[i].top();
        today[i].pop();
        if(not today[i].empty())
            summary.emplace(today[i].top(), i);
    }

    cout << result << endl;
}
