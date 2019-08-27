// Creates a dominator tree in a DAG.
// Last revision: March 2019

#pragma once

#include <algorithm>
#include <vector>
#include <cstdint>
#include <functional>

using std::vector; using std::pair;
using std::function;
using std::swap;
using std::size_t;

using graph_t = vector<vector<size_t>>;

vector<size_t> src_topological(const graph_t& graph, size_t source)
{
    const size_t n = graph.size();
    vector<size_t> indegree(n);
    vector<size_t> V; vector<bool> vis(n);
    function<void(size_t)> dfs_explore = [&](size_t u) {
        vis[u] = true;
        V.push_back(u);
        for(size_t v : graph[u])
            if(not vis[v])
                dfs_explore(v);
    };
    dfs_explore(source);
    for(size_t u : V)
        for(size_t v : graph[u])
            indegree[v]++;
    vector<size_t> T; T.reserve(V.size());
    T.push_back(source);
    for(size_t t = 0; t < T.size(); t++)
    {
        size_t u = T[t];
        for(size_t v : graph[u])
            if(--indegree[v] == 0)
                T.push_back(v);
    }
    return T;
}

pair<vector<size_t>, vector<size_t>> dag_dominators(const graph_t& graph, size_t root)
{
    const size_t n = graph.size();
    vector<size_t> idom(n, SIZE_MAX), id_depth(n, 0);
    vector<vector<size_t>> id_jump(n);

    auto lca = [&](size_t u, size_t v) {
        if(id_depth[u] > id_depth[v]) swap(u, v);
        for(size_t k = id_jump[v].size(); k --> 0; )
            if(id_depth[v] >= id_depth[u] + (1u << k))
                v = id_jump[v][k];
        if(u == v) return v;
        for(size_t k = id_jump[v].size(); k --> 0; )
            if(k < id_jump[u].size() and id_jump[u][k] != id_jump[v][k])
                u = id_jump[u][k], v = id_jump[v][k];
        return id_jump[u][0];
    };

    auto T = src_topological(graph, root);

    graph_t ingraph(n);
    for(size_t u : T)
        for(size_t v : graph[u])
            ingraph[v].push_back(u);

    for(size_t u : T)
    {
        if(ingraph[u].empty())
            continue;
        size_t a = ingraph[u][0];
        for(size_t v : ingraph[u])
            a = lca(a, v);
        idom[u] = a;
        id_jump[u].push_back(a);
        for(size_t k = 1; true; k++)
        {
            size_t v = id_jump[u][k-1];
            if(id_jump[v].size() >= k)
                id_jump[u].push_back(id_jump[v][k-1]);
            else
                break;
        }
        id_depth[u] = id_depth[a] + 1;
    }

    return {idom, T};
}
