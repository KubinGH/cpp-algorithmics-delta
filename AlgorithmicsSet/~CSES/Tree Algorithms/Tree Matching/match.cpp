#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<vector<size_t>> graph(n + 1);
    for(size_t i = 1; i < n; i++)
    {
        size_t u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    function<pair<int, int>(size_t, size_t)> solve = [&](size_t u, size_t lock) {
        pair<int, int> result = {0, 0};
        int best_gain = 0;
        for(auto v : graph[u]) if(v != lock)
        {
            auto sub = solve(v, u);
            result.first += sub.second;
            best_gain = max(best_gain, sub.first - sub.second + 1);
        }
        result.second = result.first + best_gain;
        return result;
    };
    auto r = solve(1, 0);
    cout << max(r.first, r.second) << endl;
}
