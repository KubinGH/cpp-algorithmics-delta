#include <bits/stdc++.h>

using namespace std;

using graph_t = vector<vector<size_t>>;


graph_t read_graph()
{
    size_t n;
    cin >> n;

    graph_t graph(n);
    for(size_t i = 0; i < n - 1; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    return graph;
}

array<size_t, 2> find_max_is(const graph_t& graph, size_t u, size_t lock = 0)
{
    array<size_t, 2> ret = {0, 1};
    for(auto v : graph[u]) if(v != lock)
    {
        auto sub = find_max_is(graph, v, u);
        ret[1] += sub[0];
        ret[0] += sub[1];
    }
    ret[1] = max(ret[0], ret[1]);
    return ret;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    cout << find_max_is(read_graph(), 0)[1];
}
