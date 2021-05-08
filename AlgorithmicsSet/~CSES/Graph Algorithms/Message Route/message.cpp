#include <bits/stdc++.h>

using namespace std;

const size_t nul = SIZE_MAX;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<size_t>> graph(n+1);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<size_t> back(n+1);
    queue<size_t> que;
    auto maybe = [&](size_t u, size_t b) {
        if(not back[u])
            back[u] = b, que.push(u);
    };
    maybe(1, nul);
    while(not que.empty())
    {
        auto u = que.front(); que.pop();
        for(auto v : graph[u])
            maybe(v, u);
    }
    if(back[n])
    {
        vector<size_t> path;
        size_t u = n;
        while(u != nul)
            path.push_back(u), u = back[u];
        reverse(path.begin(), path.end());
        cout << path.size() << endl;
        for(auto v : path)
            cout << v << ' ';
        cout << endl;
    }
    else
        cout << "IMPOSSIBLE";
}
