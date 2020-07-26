#include <bits/stdc++.h>

using namespace std;

struct disjoint_sets
{
    vector<size_t> repr, rank;

    disjoint_sets(size_t n) : repr(n), rank(n)
    {
        for(size_t i = 0; i < n; i++)
            repr[i] = i;
    }

    size_t find(size_t v)
    {
        return v == repr[v] ? v : repr[v] = find(repr[v]);
    }

    bool unite(size_t u, size_t v)
    {
        if((u = find(u)) == (v = find(v)))
            return false;
        if(rank[u] > rank[v])
            swap(u, v);
        rank[v] += (rank[u] == rank[v]);
        repr[u] = v;
        return true;
    }
};

enum BambooForestStatus
{
    Ok,
    Cycles,
    Bad
};

struct bamboo_forest
{
    BambooForestStatus status = Ok;
    disjoint_sets dsets;
    vector<size_t> deg;
    size_t cycles = 0;

    bamboo_forest(size_t n) : dsets(n), deg(n) {}
    bamboo_forest() : bamboo_forest(0) {}

    BambooForestStatus edge(size_t u, size_t v)
    {
        deg[u]++; deg[v]++;
        if(deg[u] > 2 or deg[v] > 2)
            status = Bad;
        if((status == Ok or status == Cycles) and dsets.find(u) == dsets.find(v) and deg[u] == 2 and deg[v] == 2)
            status = Cycles, cycles++;
        else if(not dsets.unite(u, v))
            status = Bad;
        return status;
    }
};

size_t n;
vector<pair<size_t, size_t>> edges;
vector<vector<size_t>> graph;
bamboo_forest base;
size_t first_cycle_size;

bool verybad = false;
size_t w2 = SIZE_MAX, w3 = SIZE_MAX;
bamboo_forest drop_w3;
vector<pair<size_t, bamboo_forest>> drop_w2s;

void Init(int _n)
{
    n = _n;
    base = bamboo_forest(n);
    graph.resize(n);
}

bamboo_forest current_forest_with_drop(size_t w)
{
    bamboo_forest F(n);
    for(auto [u, v] : edges)
        if(u != w and v != w)
            F.edge(u, v);
    return F;
}

void Link(int _u, int _v)
{
    size_t u = _u, v = _v;

    edges.emplace_back(u, v);
    graph[u].push_back(v);
    graph[v].push_back(u);

    auto pre = base.status;
    base.edge(u, v);

    if(pre == Ok and base.status == Cycles and base.cycles == 1)
    {
        auto w = base.dsets.find(u);
        for(size_t i = 0; i < n; i++)
            if(base.dsets.find(i) == w)
                first_cycle_size++;
    }

    if((base.deg[u] > 3 or base.deg[v] > 3) and w3 == SIZE_MAX)
        drop_w3 = current_forest_with_drop(w3 = (base.deg[u] > 3 ? u : v));
    else if(w3 != SIZE_MAX and u != w3 and v != w3)
        drop_w3.edge(u, v);

    if(w3 != SIZE_MAX and base.deg[u] > 3 and u != w3)
        verybad = true;
    if(w3 != SIZE_MAX and base.deg[v] > 3 and v != w3)
        verybad = true;

    if((base.deg[u] > 2 or base.deg[v] > 2) and w2 == SIZE_MAX and w3 == SIZE_MAX)
    {
        w2 = base.deg[u] > 2 ? u : v;
        drop_w2s.resize(graph[w2].size() + 1, {SIZE_MAX, bamboo_forest(n)});
        for(size_t i = 0; i < graph[w2].size(); i++)
            drop_w2s[1+i] = {graph[w2][i], current_forest_with_drop(graph[w2][i])};
        drop_w2s[0] = {w2, current_forest_with_drop(w2)};
    }
    else if(w3 == SIZE_MAX and w2 != SIZE_MAX)
    {
        for(auto& [w, F] : drop_w2s)
            if(u != w and v != w)
                F.edge(u, v);
    }
}

bool naive_try(size_t i)
{
    return current_forest_with_drop(i).status == Ok;
}

int CountCritical()
{
    if(verybad)
        return 0;
    else if(base.status == Ok)
        return n;
    else if(base.status == Cycles and base.cycles == 1)
        return first_cycle_size;
    else if(base.status == Cycles and base.cycles > 1)
        return 0;
    else
    {
        if(w3 != SIZE_MAX)
            return drop_w3.status == Ok;

        size_t result = 0;
        for(auto& [_, F] : drop_w2s)
            result += F.status == Ok;
        return result;
    }
}
