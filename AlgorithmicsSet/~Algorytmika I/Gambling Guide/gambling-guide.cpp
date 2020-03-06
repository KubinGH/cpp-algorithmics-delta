#include <bits/stdc++.h>

using namespace std;

template<typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<size_t>> graph(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<size_t> less_deg(n);
    vector<double> e(n, numeric_limits<double>::infinity()), less_e(n);

    auto E = [&](size_t u) {
        return (less_e[u] + graph[u].size()) / less_deg[u];
    };

    min_priority_queue<pair<double, size_t>> Q;
    vector<bool> lock(n);

    Q.emplace(0, n-1);
    while(not Q.empty())
    {
        size_t u = Q.top().second; Q.pop();

        if(lock[u]) continue;
        lock[u] = true;
        e[u] = less_deg[u] ? E(u) : 0;

        for(auto v : graph[u]) if(not lock[v])
        {
            less_e[v] += e[u];
            less_deg[v]++;
            Q.emplace(E(v), v);
        }
    }

    cout << fixed << setprecision(8) << e.front();
}
