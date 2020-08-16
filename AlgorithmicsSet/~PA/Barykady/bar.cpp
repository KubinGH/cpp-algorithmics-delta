#include <bits/stdc++.h>

using namespace std;

const size_t N = 1 << 12;

vector<size_t> graph[N];

vector<int> solve(size_t u, vector<int>& result, size_t lock = SIZE_MAX)
{
    vector<int> cost = {0, (int)graph[u].size()};
    for(auto v : graph[u]) if(v != lock)
    {
        auto sub = solve(v, result, u);
        cost.resize(cost.size() + sub.size() - 1, INT_MAX/3);
        for(size_t k = cost.size(); k --> 1; )
            for(size_t i = 1; i < sub.size() and i < k; i++)
                cost[k] = min(cost[k], cost[k-i] + sub[i] - 2);
    }

    for(size_t i = 0; i < cost.size() and i < result.size(); i++)
        result[i] = min(result[i], cost[i]);

    return cost;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    for(size_t i = 0; i < n - 1; i++)
    {
        size_t u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> cost(n + 1, INT_MAX/3);
    solve(1, cost);

    size_t m;
    cin >> m;

    while(m --> 0)
    {
        size_t k;
        cin >> k;
        cout << cost[k] << '\n';
    }
}
