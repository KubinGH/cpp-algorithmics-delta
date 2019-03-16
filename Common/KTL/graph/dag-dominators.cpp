// Creates a dominator tree in a DAG.
// Last revision: March 2019

#pragma once

#include <vector>
#include <cstdint>
#include <functional>

using namespace std;

using graph_t = vector<vector<uint32_t>>;

vector<uint32_t> src_topological(const graph_t& graph, uint32_t source)
{
    const uint32_t n = graph.size();
    vector<uint32_t> indegree(n);
    vector<uint32_t> V; vector<bool> vis(n);
    function<void(uint32_t)> dfs_explore = [&](uint32_t u) {
        vis[u] = true;
        V.push_back(u);
        for(uint32_t v : graph[u])
            if(not vis[v])
                dfs_explore(v);
    };
    dfs_explore(source);
    for(uint32_t u : V)
        for(uint32_t v : graph[u])
            indegree[v]++;
    vector<uint32_t> T; T.reserve(V.size());
    T.push_back(source);
    for(uint32_t t = 0; t < T.size(); t++)
    {
        uint32_t u = T[t];
        for(uint32_t v : graph[u])
            if(--indegree[v] == 0)
                T.push_back(v);
    }
    return T;
}

pair<vector<uint32_t>, vector<uint32_t>> dag_dominators(const graph_t& graph, uint32_t root)
{
    const uint32_t n = graph.size();
    vector<uint32_t> idom(n, -1u), id_depth(n, 0);
    vector<vector<uint32_t>> id_jump(n);

    auto lca = [&](uint32_t u, uint32_t v) {
        if(id_depth[u] > id_depth[v]) swap(u, v);
        for(uint32_t k = id_jump[v].size(); k --> 0; )
            if(id_depth[v] >= id_depth[u] + (1u << k))
                v = id_jump[v][k];
        if(u == v) return v;
        for(uint32_t k = id_jump[v].size(); k --> 0; )
            if(id_jump[u][k] != id_jump[v][k])
                u = id_jump[u][k], v = id_jump[v][k];
        return id_jump[u][0];
    };

    auto T = src_topological(graph, root);

    graph_t ingraph(n);
    for(uint32_t u : T)
        for(uint32_t v : graph[u])
            ingraph[v].push_back(u);

    for(uint32_t u : T)
    {
        if(ingraph[u].empty())
        {
            idom[u] = -1u;
            continue;
        }
        uint32_t a = ingraph[u][0];
        for(uint32_t v : ingraph[u])
            a = lca(a, v);
        idom[u] = a;
        id_jump[u].push_back(a);
        for(uint32_t k = 1; true; k++)
        {
            uint32_t v = id_jump[u][k-1];
            if(id_jump[v].size() >= k)
                id_jump[u].push_back(id_jump[v][k-1]);
            else
                break;
        }
        id_depth[u] = id_depth[a] + 1;
    }

    return {idom, T};
}