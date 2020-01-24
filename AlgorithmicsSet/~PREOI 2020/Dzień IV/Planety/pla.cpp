#include <bits/stdc++.h>

using namespace std;

using edge = pair<size_t, int64_t>;
const int64_t oo = INT64_MAX / 3;

vector<vector<edge>> graph;
vector<size_t> parent, order;

void dfs(size_t u)
{
    for(auto [v, s] : graph[u])
        if(v != parent[u])
            parent[v] = u, dfs(v);
    order.push_back(u);
}

vector<int64_t> T, M, M2;
vector<size_t> MI;

int64_t fun(size_t v, int64_t s)
{
    return max(T[v], M[v] + s);
}

void updateM(size_t u, size_t v, int64_t s)
{
    auto c = T[u] - fun(v, s) + T[v] + s;
    if(c >= M[u])
        M2[u] = M[u], M[u] = c, MI[u] = v;
    else if(c > M2[u])
        M2[u] = c;
}

void recompute(size_t u)
{
    T[u] = 0;
    M[u] = M2[u] = -oo;
    MI[u] = SIZE_MAX;

    for(auto [v, s] : graph[u]) if(v != parent[u])
        T[u] += fun(v, s);

    for(auto [v, s] : graph[u]) if(v != parent[u])
        updateM(u, v, s);
}

void dfs_tour(size_t u, size_t p, int64_t& result)
{
    result = max(result, T[u]);

    for(auto [v, s] : graph[u]) if(v != p)
    {
        parent[v] = parent[u] = v;

        auto reMu = M[u], reMv = M[v], reM2v = M2[v];
        auto reMIv = MI[v];

        T[u] -= fun(v, s);
        if(v == MI[u]) M[u] = M2[u];
        M[u] -= fun(v, s);
        T[v] += fun(u, s);
        M[v] += fun(u, s);
        M2[v] += fun(u, s);
        updateM(v, u, s);

        dfs_tour(v, u, result);

        parent[u] = parent[v] = u;
        T[v] -= fun(u, s);
        M[v] = reMv; M2[v] = reM2v; MI[v] = reMIv;
        T[u] += fun(v, s);
        M[u] = reMu;
    }
}


int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    graph.resize(n); parent.resize(n);
    for(size_t i = 1; i < n; i++)
    {
        size_t u, v; int64_t s;
        cin >> u >> v >> s; u--; v--;
        graph[u].emplace_back(v, s);
        graph[v].emplace_back(u, s);
    }

    int64_t result = 0;

    dfs(0);

    T.resize(n);
    M.resize(n); MI.resize(n); M2.resize(n);
    for(auto u : order)
        recompute(u);

    dfs_tour(0, 0, result);

    cout << result << endl;
}
