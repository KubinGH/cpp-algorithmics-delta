#include <bits/stdc++.h>

using namespace std;

vector<vector<size_t>> adj;
vector<vector<pair<size_t, int>>> graph;

const int oo = INT_MAX / 3;

int& rd(unordered_map<int, int>& m, int key)
{
    auto it = m.find(key);
    if(it == m.end()) it = m.emplace_hint(it, key, +oo);
    return it->second;
}

void mini(unordered_map<int, int>& m, int key, int value)
{
    rd(m, key) = min(rd(m, key), value);
}

size_t gl_vertices;
vector<size_t> gl_parent, gl_subsize;
vector<bool> gl_lock;

void dfs_map_paths(size_t u, int s, int d, unordered_map<int, int>& m,
                   size_t lock = SIZE_MAX)
{
    if(d > +oo) return;
    mini(m, s, d);
    for(auto [v, w] : graph[u])
        if(v != lock and not gl_lock[v])
            dfs_map_paths(v, s + w, d + 1, m, u);
}

void dfs_root(size_t u, size_t glock = SIZE_MAX, size_t lock = SIZE_MAX)
{
    gl_vertices++;
    gl_subsize[u] = 1;
    for(auto v : adj[u])
        if(v != lock and not gl_lock[v])
            gl_parent[v] = u, dfs_root(v, glock, u), gl_subsize[u] += gl_subsize[v];
}

size_t subtree_size(size_t from, size_t to)
{
    return from == gl_parent[to] ? gl_subsize[to] : gl_vertices - gl_subsize[from];
}

size_t find_centroid(size_t init)
{
    gl_vertices = 0;

    dfs_root(init);
    gl_parent[init] = SIZE_MAX;

    size_t u = init;
    while(true)
    {
        bool any = false;
        for(auto v : adj[u])
            if(not gl_lock[v] and subtree_size(u, v) > subtree_size(v, u))
                { any = true; u = v; break; }
        if(not any) break;
    }

    return u;
}


int solve(size_t init, int k)
{
    auto fix = find_centroid(init);

    int result = +oo;

    unordered_map<int, int> pre = {{0, 0}};
    pre.reserve(4 * gl_vertices);
    gl_lock[fix] = true;
    for(auto [v, w] : graph[fix])
      if(not gl_lock[v])
    {
        unordered_map<int, int> cur;
        cur.reserve(4 * subtree_size(fix, v));
        dfs_map_paths(v, w, 1, cur);

        for(auto [s, d] : cur)
            result = min(result, d + rd(pre, k - s));
        for(auto [s, d] : cur)
            mini(pre, s, d);
    }

    for(auto v : adj[fix])
        if(not gl_lock[v])
            result = min(result, solve(v, k));

    return result;
}


int best_path(int _n, int k, int H[][2], int L[])
{
    const size_t n = _n;

    graph.resize(n);
    adj.resize(n);
    for(size_t i = 0; i < n - 1; i++)
    {
        graph[H[i][0]].emplace_back(H[i][1], L[i]);
        graph[H[i][1]].emplace_back(H[i][0], L[i]);
        adj[H[i][0]].push_back(H[i][1]);
        adj[H[i][1]].push_back(H[i][0]);
    }

    gl_lock.resize(n);
    gl_parent.resize(n);
    gl_subsize.resize(n);
    int result = solve(0, k);

    return result >= +oo ? -1 : result;
}
