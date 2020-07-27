#include <bits/stdc++.h>

using namespace std;

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

    vector<size_t> leaves(n);
    for(size_t u = 0; u < n; u++)
        for(auto v : graph[u])
            if(graph[v].size() == 1)
                leaves[u]++;

    queue<size_t> Q;

    auto sat = [&](size_t u) {
        return leaves[u] and graph[u].size() - leaves[u] <= 1;
    };

    auto rem = [&](size_t u, size_t v) {
        graph[u].erase(find(graph[u].begin(), graph[u].end(), v));
        graph[v].erase(find(graph[v].begin(), graph[v].end(), u));
        if(graph[v].size() == 1)
        {
            leaves[graph[v][0]]++;
            if(sat(graph[v][0]))
                Q.push(graph[v][0]);
        }
        else if(sat(v))
            Q.push(v);
    };

    for(size_t u = 0; u < n; u++)
        if(sat(u))
            Q.push(u);

    size_t result = 0;
    vector<size_t> to(n, SIZE_MAX);
    size_t m = n;
    while(m)
    {
        size_t par;
        while(true)
        {
            par = Q.front(); Q.pop();
            if(to[par] == SIZE_MAX)
                break;
        }

        size_t notleaf = SIZE_MAX;
        for(auto u : graph[par])
            if(graph[u].size() > 1)
                notleaf = u;

        if(notleaf != SIZE_MAX)
            rem(par, notleaf);

        size_t last = par;
        graph[par].push_back(par);
        for(auto u : graph[par])
        {
            result += (last == par or u == par ? 1 : 2);
            to[last] = u;
            last = u;
        }
        m -= graph[par].size();
    }

    cout << result << endl;
    for(size_t i = 0; i < n; i++)
        cout << to[i]+1 << ' ';
    cout << endl;
}
