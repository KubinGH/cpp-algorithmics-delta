// TLE?
#include <bits/stdc++.h>

using namespace std;

struct bipartite_matching
{
    using graph_t = vector<vector<uint32_t>>;

    const graph_t& graph;
    uint32_t n;
    vector<uint32_t> vis, match;
    uint32_t timepoint = 1;
    static constexpr uint32_t NONMATCHED = SIZE_MAX;

    bipartite_matching(const graph_t& _graph)
        : graph(_graph), n(graph.size()), vis(n), match(n) {}

    void dfs_color(uint32_t u, vector<uint32_t>& out, bool c = true)
    {
        vis[u] = timepoint;
        if(c) out.push_back(u);
        for(auto v : graph[u])
            if(vis[v] < timepoint)
                dfs_color(v, out, not c);
    }

    vector<uint32_t> find_colored()
    {
        vector<uint32_t> colored;
        timepoint++;
        for(uint32_t u = 0; u < n; u++)
            if(vis[u] < timepoint)
                dfs_color(u, colored);
        return colored;
    }

    bool dfs_match(uint32_t u)
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

    vector<uint32_t> operator() (const vector<uint32_t>& colored)
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
    uint32_t n1, n2, m;
    cin >> n1 >> n2 >> m;
    vector<vector<uint32_t>> graph(n1+n2);
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(n1+v);
        graph[n1+v].push_back(u);
    }
    auto matcher = bipartite_matching{graph};
    auto match = matcher(matcher.find_colored());
    uint32_t result = 0;
    for(uint32_t u = 0; u < n1; u++)
        if(match[u] != bipartite_matching::NONMATCHED)
            result++;
    cout << result;
}
