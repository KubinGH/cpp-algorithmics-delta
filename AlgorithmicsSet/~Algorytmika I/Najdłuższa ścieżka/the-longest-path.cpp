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

pair<size_t, uint> max_path_from(const graph_t& graph, size_t u, size_t lock = SIZE_MAX)
{
    pair<size_t, uint> ret = {u, 0};
    for(auto v : graph[u]) if(v != lock)
    {
        auto sub = max_path_from(graph, v, u);
        sub.second++;
        if(sub.second > ret.second)
            ret = sub;
    }
    return ret;
}

bool print_path(const graph_t& graph, size_t u, size_t target, size_t lock = SIZE_MAX)
{
    if(u == target)
    {
        cout << u+1 << " ";
        return true;
    }
    for(auto v : graph[u]) if(v != lock)
    {
        if(print_path(graph, v, target, u))
        {
            cout << u+1 << " ";
            return true;
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    auto graph = read_graph();
    auto furthest0 = max_path_from(graph, 0);
    auto furthest = max_path_from(graph, furthest0.first);
    cout << furthest.second << endl;
    print_path(graph, furthest0.first, furthest.first);
    cout << endl;
}
