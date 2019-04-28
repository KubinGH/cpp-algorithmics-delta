#include <bits/stdc++.h>

using namespace std;

struct bipartite_matching
{
    using graph_t = vector<vector<size_t>>;

    const graph_t& graph;
    size_t n;
    vector<bool> vis;
    vector<size_t> match;

    bipartite_matching(const graph_t& _graph)
        : graph(_graph), n(graph.size()), vis(n), match(n, SIZE_MAX) {}

    void dfs_color(size_t u, vector<size_t>& out, bool c = true)
    {
        vis[u] = true;
        if(c) out.push_back(u);
        for(auto v : graph[u])
            if(not vis[v])
                dfs_color(v, out, not c);
    }

    vector<size_t> find_colored()
    {
        vector<size_t> colored;
        colored.reserve(n);
        fill(vis.begin(), vis.end(), false);
        for(size_t u = 0; u < n; u++)
            if(not vis[u])
                dfs_color(u, colored);
        return colored;
    }

    bool dfs_match(size_t u)
    {
        vis[u] = true;
        for(auto v : graph[u])
        {
            if(match[v] == SIZE_MAX)
            {
                match[u] = v; match[v] = u;
                return true;
            }
        }
        for(auto v : graph[u])
        {
            if(not vis[match[v]] and dfs_match(match[v]))
            {
                match[u] = v; match[v] = u;
                return true;
            }
        }
        return false;
    }

    vector<size_t> operator() (const vector<size_t>& colored)
    {
        fill(match.begin(), match.end(), SIZE_MAX);

        bool any = true;
        while(any)
        {
            any = false;
            fill(vis.begin(), vis.end(), false);
            for(auto u : colored)
                if(match[u] == SIZE_MAX and dfs_match(u))
                    any = true;
        }
        return match;
    }

    vector<size_t> operator() ()
    {
        auto colored = find_colored();
        return operator() (colored);
    }
};

int main()
{
    size_t n, m;
    cin >> n >> m;
    vector<vector<bool>> lock(n, vector<bool>(n));
    for(size_t i = 0; i < m; i++)
    {
        size_t x, y;
        cin >> x >> y; x--; y--;
        lock[x][y] = true;
    }

    vector<vector<size_t>> graph(n * n);

    auto conn = [&](size_t x1, size_t y1, size_t x2, size_t y2)
    {
        if(x1 >= n or y1 >= n or x2 >= n or y2 >= n or
           lock[x1][y1] or lock[x2][y2])
            return;
        size_t i = x1 + y1*n, j = x2 + y2*n;
        graph[i].push_back(j);
        graph[j].push_back(i);
    };

    for(size_t y = 0; y < n; y++)
        for(size_t x = 0; x < n; x++)
    {
        conn(x, y, x + 1, y - 2);
        conn(x, y, x + 2, y - 1);
        conn(x, y, x + 2, y + 1);
        conn(x, y, x + 1, y + 2);
    }

    auto match = bipartite_matching{graph}();

    size_t max_matching = 0;

    for(size_t y = 0, i = 0; y < n; y++)
        for(size_t x = 0; x < n; x++, i++)
            if(not lock[x][y] and match[i] != SIZE_MAX)
                max_matching++;

    size_t max_independent_set = (n*n - m) - (max_matching /= 2);

    cout << max_independent_set;
}
