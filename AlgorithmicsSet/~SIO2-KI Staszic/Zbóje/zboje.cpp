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
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    size_t n1, n2;
    cin >> n1 >> n2;
    vector<vector<size_t>> graph(n1+n2);
    size_t u, v;
    while(cin >> u >> v, u and v)
    {
        u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<size_t> colored(n1);
    iota(colored.begin(), colored.end(), 0);
    auto match = bipartite_matching{graph}(colored);
    size_t result = n1 + n2;
    for(size_t i = 0; i < n1; i++)
        if(match[i] != SIZE_MAX)
            result--;
    cout << result << endl;
}
