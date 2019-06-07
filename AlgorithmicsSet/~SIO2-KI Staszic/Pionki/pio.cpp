#include <bits/stdc++.h>

using namespace std;

vector<size_t> topological_sort(const vector<vector<size_t>>& graph)
{
    const size_t n = graph.size();
    vector<size_t> indegree(n);
    for(size_t u = 0; u < n; u++)
        for(size_t v : graph[u])
            indegree[v]++;
    vector<size_t> T; T.reserve(n);
    for(size_t u = 0; u < n; u++)
        if(not indegree[u])
            T.push_back(u);
    for(size_t t = 0; t < T.size(); t++)
    {
        size_t u = T[t];
        for(size_t v : graph[u])
            if(--indegree[v] == 0)
                T.push_back(v);
    }
    return T;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n, m, k;
    cin >> n >> m >> k;

    vector<size_t> pawns(k);
    for(size_t i = 0; i < k; i++)
        cin >> pawns[i], pawns[i]--;
    vector<vector<size_t>> graph(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
    }

    auto order = topological_sort(graph);

    reverse(order.begin(), order.end());

    vector<int> delay(n);
    vector<bool> win(n);

    for(auto u : order)
    {
        for(auto v : graph[u])
            if(not win[v])
                win[u] = true;
        if(win[u])
        {
            delay[u] = INT_MAX;
            for(auto v : graph[u])
                if(not win[v])
                    delay[u] = min(delay[u], delay[v] + 1);
        }
        else
        {
            delay[u] = 0;
            for(auto v : graph[u])
                delay[u] = max(delay[u], delay[v] + 1);
        }
    }

    int first_loser = INT_MAX, first_winner = INT_MAX;

    for(auto u : pawns)
    {
        if(win[u])
            first_winner = min(first_winner, delay[u]);
        else
            first_loser = min(first_loser, delay[u]);
    }

    cout << (first_winner <= first_loser ? "T" : "R") << endl;
}
