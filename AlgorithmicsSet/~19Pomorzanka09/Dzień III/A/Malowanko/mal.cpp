#include <bits/stdc++.h>

using namespace std;

using graph_t = vector<vector<pair<size_t, int>>>;

struct dfs
{
    const graph_t& graph;
    vector<bool> vis;
    dfs(const graph_t& _graph) : graph(_graph), vis(graph.size()) {}
    void mark(size_t u, vector<size_t>& out)
    {
        out.push_back(u);
        vis[u] = true;
        for(auto e : graph[u])
            if(not vis[e.first])
                mark(e.first, out);
    }
    bool color3(size_t u, vector<int>& color)
    {
        vis[u] = true;
        for(auto e : graph[u])
        {
            size_t v = e.first; int s = e.second;
            if(not vis[v])
                color[v] = (3+color[u]+s) % 3, color3(v, color);
        }
        return true;
    }
};

vector<vector<size_t>> components(const graph_t& graph)
{
    const size_t n = graph.size();
    vector<vector<size_t>> out;
    dfs S(graph);
    for(size_t s = 0; s < n; s++)
    {
        if(S.vis[s])
            continue;
        out.emplace_back();
        S.mark(s, out.back());
    }
    return out;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    graph_t graph(n);

    for(size_t i = 0; i < m; i++)
    {
        size_t x, y;
        cin >> x >> y; x--; y--;
        graph[x].emplace_back(y, 1);
        graph[y].emplace_back(x, -1);
    }

    vector<int> color(n);
    uint64_t result = 0;
    for(auto vertices : components(graph))
    {
        dfs{graph}.color3(vertices[0], color);

        bool ok = true;
        for(auto u : vertices)
            for(auto e : graph[u])
                if(color[e.first] != (3+color[u]+e.second) % 3)
                    ok = false;

        if(not ok)
            result += (uint64_t)vertices.size() * vertices.size();
        else
        {
            uint64_t occ[3] = {0, 0, 0};
            for(auto u : vertices)
                occ[color[u]]++;
            if(occ[0] == 0 or occ[1] == 0 or occ[2] == 0)
            {
                size_t r = 0;
                for(auto u : vertices)
                    r += graph[u].size();
                result += r / 2;
            }
            else
                result += occ[0]*occ[1] + occ[0]*occ[2] + occ[1]*occ[2];
        }
    }
    cout << result;
}
