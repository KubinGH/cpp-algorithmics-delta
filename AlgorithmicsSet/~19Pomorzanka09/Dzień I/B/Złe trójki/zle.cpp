#include <bits/stdc++.h>

using namespace std;

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

    for(size_t u = 0; u < n; u++)
        sort(graph[u].begin(), graph[u].end());

    array<size_t, 3> result = {SIZE_MAX, SIZE_MAX, SIZE_MAX};

    auto maybe = [&](array<size_t, 3> candy) {
        sort(candy.begin(), candy.end());
        result = min(result, candy);
    };

    size_t max_degree = 0;
    for(size_t u = 0; u < n; u++)
    {
        max_degree = max(max_degree, graph[u].size());
        if(graph[u].size() >= 3)
        {
            size_t x = graph[u][0], y = graph[u][1], z = graph[u][2];
            bool block = false;
            for(size_t i = 0; i < 3; i++)
            {
                if(binary_search(graph[x].begin(), graph[x].end(), y))
                    block = true, maybe({u, x, y});
                if(i == 0)
                    swap(x, y);
                else if(i == 1)
                    swap(x, z);
                else
                    swap(x, z), swap(x, y);
            }
            if(not block)
                maybe({x, y, z});
        }
    }

    if(max_degree < 3 and n == m and n % 3 == 0)
    {
        auto after = [&](size_t u, size_t b) {
            return graph[u][graph[u][0] == b];
        };
        size_t u = 1, b = 1, x = u, y, z;
        for(size_t k = 0, bb; k < n/3; k++)
            bb = u, u = after(u, b), b = bb;
        y = u;
        for(size_t k = 0, bb; k < n/3; k++)
            bb = u, u = after(u, b), b = bb;
        z = u;
        maybe({x, y, z});
    }

    if(result[0] != SIZE_MAX)
        cout << result[0] << " " << result[1] << " " << result[2] << endl;
    else
        cout << -1 << endl;
}
