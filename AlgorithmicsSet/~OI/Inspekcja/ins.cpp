#include <bits/stdc++.h>

using namespace std;

vector<vector<size_t>> graph;
vector<size_t> parent;
vector<int> max_dist, max_dist_2nd, subtree;
vector<int64_t> sum_dist, result;

void dp_conn(size_t u, size_t v)
{
    auto d = max_dist[v] + 1;
    if(d >= max_dist[u])
        max_dist_2nd[u] = max_dist[u], max_dist[u] = d;
    else if(d > max_dist_2nd[u])
        max_dist_2nd[u] = d;

    subtree[u] += subtree[v];
    sum_dist[u] += sum_dist[v] + subtree[v];
}

void dfs_root(size_t u)
{
    subtree[u] = 1;
    max_dist[u] = max_dist_2nd[u] = sum_dist[u] = 0;
    for(auto v : graph[u]) if(v != parent[u])
    {
        parent[v] = u;
        dfs_root(v);
        dp_conn(u, v);
    }
}

int64_t get_result_of_root(size_t u)
{
    int s = 0, x = 0, v_x = -1;
    for(auto v : graph[u])
    {
        s += subtree[v];
        if(subtree[v] > x)
            x = subtree[v], v_x = v;
    }
    if(2*x == s+1)
        return 2*sum_dist[u] - (max_dist[v_x] + 1);
    else if(2*x <= s)
        return 2*sum_dist[u] - max_dist[u];
    else
        return -1;
}

void dfs_travel(size_t u, size_t lock = SIZE_MAX)
{
    result[u] = get_result_of_root(u);

    for(auto v : graph[u]) if(v != lock)
    {
        #define SAVE_EXPR(w) max_dist[w], max_dist_2nd[w], subtree[w], sum_dist[w]
        auto u_save = make_tuple(SAVE_EXPR(u)), v_save = make_tuple(SAVE_EXPR(v));

        if(max_dist[u] == max_dist[v] + 1)
            max_dist[u] = max_dist_2nd[u], max_dist_2nd[u] = 0;
        subtree[u] -= subtree[v];
        sum_dist[u] -= sum_dist[v] + subtree[v];
        dp_conn(v, u);
        
        dfs_travel(v, u);
        tie(SAVE_EXPR(u)) = u_save; tie(SAVE_EXPR(v)) = v_save;
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    graph.resize(n);
    parent.resize(n, SIZE_MAX);
    max_dist.resize(n); max_dist_2nd.resize(n);
    subtree.resize(n); sum_dist.resize(n);
    result.resize(n, -1);

    for(size_t i = 0; i < n - 1; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs_root(0);
    dfs_travel(0);

    for(size_t u = 0; u < n; u++)
        cout << result[u] << '\n';
}
