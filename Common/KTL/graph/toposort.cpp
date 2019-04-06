#pragma once

#include <vector>
#include <cstddef>

using std::vector;
using std::size_t;

vector<size_t> topological_sort(const vector<vector<size_t>>& graph)
{
    const size_t n = graph.size();
    vector<size_t> indegree(n);
    for(size_t u = 0; u < n; u++)
        for(size_t v : graph[u])
            indegree[v]++;
    vector<size_t> T; T.reserve(n);
    for(size_t u = 0; u < n; u++)
        if(not indegree[u])
            T.push_back(u);
    for(size_t t = 0; t < T.size(); t++)
    {
        size_t u = T[t];
        for(size_t v : graph[u])
            if(--indegree[v] == 0)
                T.push_back(v);
    }
    return T;
}
