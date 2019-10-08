#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<vector<size_t>> graph(n);
    for(size_t i = 0; i < n - 1; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<bool> visited(n);
    vector<uint> time_of(n, UINT_MAX);
    uint the_time = 0;
    set<pair<uint, size_t>> tovis;
    tovis.emplace(time_of[0] = 0, 0);

    for(size_t i = 0; i < n; i++)
    {
        size_t u;
        cin >> u; u--;

        visited[u] = true;

        if(tovis.empty() or time_of[u] > tovis.begin()->first or
           tovis.find({time_of[u], u}) == tovis.end())
        {
            cout << "No";
            return 0;
        }
        tovis.erase({time_of[u], u});

        the_time++;
        for(auto v : graph[u])
            if(not visited[v])
                tovis.emplace(time_of[v] = the_time, v);
    }

    cout << "Yes";
}
