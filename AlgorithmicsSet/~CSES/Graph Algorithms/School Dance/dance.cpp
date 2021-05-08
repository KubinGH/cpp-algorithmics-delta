#include <bits/stdc++.h>

using namespace std;

const size_t nul = SIZE_MAX;

struct bipartite_matching
{
    vector<size_t> match;
    vector<bool> vis;
    const vector<vector<size_t>>& graph;

    bipartite_matching(const vector<vector<size_t>>& g) : graph(g) {}

    bool augment(size_t u)
    {
        if(vis[u])
            return false;
        vis[u] = true;
        for(auto v : graph[u])
            if(match[v] == nul)
                { match[u] = v; match[v] = u; return true; }
        for(auto v : graph[u])
            if(augment(match[v]))
                { match[u] = v; match[v] = u; return true; }
        return false;
    }

    vector<size_t> operator() ()
    {
        const size_t n = graph.size();
        match.assign(n, nul);
        bool any = true;
        while(any)
        {
            any = false;
            vis.assign(n, false);
            for(size_t u = 0; u < n; u++)
                if(match[u] == nul and augment(u))
                    any = true;
        }
        return match;
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, k;
    cin >> n >> m >> k;

    vector<vector<size_t>> graph(n + m);
    for(size_t i = 0; i < k; i++)
    {
        size_t u, v;
        cin >> u >> v; u += -1; v += n - 1;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    auto match = bipartite_matching{graph}();
    vector<pair<size_t, size_t>> pairs;
    for(size_t i = 0; i < n; i++)
        if(match[i] != nul)
            pairs.emplace_back(i + 1, match[i] - n + 1);

    cout << pairs.size() << endl;
    for(auto [a, b] : pairs)
        cout << a << ' ' << b << '\n';
}
