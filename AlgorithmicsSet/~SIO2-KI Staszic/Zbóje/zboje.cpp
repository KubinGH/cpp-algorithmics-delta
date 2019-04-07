#include <bits/stdc++.h>

using namespace std;

struct bipartite_matching
{
    using graph_t = vector<vector<size_t>>;

    const graph_t& graph;
    size_t n;
    vector<size_t> vis, match;
    size_t timepoint = 1;
    static constexpr size_t NONMATCHED = SIZE_MAX;

    bipartite_matching(const graph_t& _graph)
        : graph(_graph), n(graph.size()), vis(n), match(n) {}

    void dfs_color(size_t u, vector<size_t>& out, bool c = true)
    {
        vis[u] = timepoint;
        if(c) out.push_back(u);
        for(auto v : graph[u])
            if(vis[v] < timepoint)
                dfs_color(v, out, not c);
    }

    vector<size_t> find_colored()
    {
        vector<size_t> colored;
        timepoint++;
        for(size_t u = 0; u < n; u++)
            if(vis[u] < timepoint)
                dfs_color(u, colored);
        return colored;
    }

    bool dfs_match(size_t u)
    {
        vis[u] = timepoint;
        for(auto v : graph[u])
        {
            if(match[v] == NONMATCHED)
            {
                match[u] = v; match[v] = u;
                return true;
            }
        }
        for(auto v : graph[u])
        {
            if(vis[match[v]] < timepoint and dfs_match(match[v]))
            {
                match[u] = v; match[v] = u;
                return true;
            }
        }
        return false;
    }

    vector<size_t> operator() (const vector<size_t>& colored)
    {
        fill(vis.begin(), vis.end(), timepoint);
        fill(match.begin(), match.end(), NONMATCHED);
        for(auto u : colored)
        {
            dfs_match(u);
            timepoint++;
        }
        return match;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n1, n2;
    cin >> n1 >> n2;
    vector<vector<uint32_t>> graph(n1+n2);
    uint32_t u, v;
    while(cin >> u >> v)
    {
        if(u == 0 and v == 0)
            break;
        u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<uint32_t> colored(n1);
    iota(colored.begin(), colored.end(), 0);
    auto match = bipartite_matching{graph}(colored);
    uint32_t result = n1 + n2;
    for(uint32_t i = 0; i < n1; i++)
        if(match[i] != bipartite_matching::NONMATCHED)
            result--;
    cout << result;
}
