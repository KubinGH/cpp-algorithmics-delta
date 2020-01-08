#include <bits/stdc++.h>

using namespace std;

using graph_t = vector<vector<pair<size_t, int>>>;

vector<char> read_colors(size_t n)
{
    vector<char> C(n);
    for(auto& c : C)
        cin >> c, c = c - '1';
    return C;
}

graph_t read_graph(size_t n, size_t m)
{
    graph_t G(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        G[u].emplace_back(v, i+1);
        G[v].emplace_back(u, i+1);
    }
    return G;
}

graph_t compress3(const graph_t& G, const vector<char>& C)
{
    graph_t F(G.size());

    for(size_t u = 0; u < G.size(); u++)
        for(auto [v, x] : G[u])
            if(C[v] == (C[u] + 1) % 3)
                F[u].emplace_back(v, x);

    return F;
}


struct bipartite_matching
{
    using graph_t = vector<vector<size_t>>;

    const graph_t& graph;
    size_t n;
    vector<bool> vis;
    vector<size_t> match;

    bipartite_matching(const graph_t& _graph)
        : graph(_graph), n(graph.size()), vis(n), match(n, SIZE_MAX) {}

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

    vector<size_t> operator() ()
    {
        fill(match.begin(), match.end(), SIZE_MAX);

        bool any = true;
        while(any)
        {
            any = false;
            fill(vis.begin(), vis.end(), false);
            for(size_t u = 0; u < n; u++)
                if(match[u] == SIZE_MAX and dfs_match(u))
                    any = true;
        }
        return match;
    }
};


int main()
{
    size_t n3, m3;
    cin >> n3 >> m3;

    auto C3 = read_colors(n3);
    auto G3 = read_graph(n3, m3);
    auto G = compress3(G3, C3);

    size_t n = G.size();

    vector<int> W;

    for(size_t u = 0; u < n; u++)
        for(auto [v, x] : G[u])
            W.push_back(x);
    sort(W.begin(), W.end());
    W.erase(unique(W.begin(), W.end()), W.end());

    size_t lo = 0, hi = W.size();
    while(lo < hi)
    {
        size_t mid = (lo + hi) / 2;

        vector<vector<size_t>> M(2*n);
        for(size_t u = 0; u < n; u++)
            for(auto [v, x] : G[u])
                if(x <= W[mid])
                    M[u].push_back(n + v), M[n + v].push_back(u);

        auto match = bipartite_matching{M}();

        if(not count(match.begin(), match.end(), SIZE_MAX))
            hi = mid;
        else
            lo = mid+1;
    }

    if(lo < W.size())
        cout << W[lo];
    else
        cout << "NO";
}
