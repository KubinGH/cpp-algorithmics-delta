#include <bits/stdc++.h>
#include <ktl/util/extio.cpp>

using namespace std;

namespace brute
{
    vector<size_t> distances(const vector<vector<size_t>>& graph)
    {
        size_t n = graph.size();
        vector<size_t> distance(n);
        vector<bool> visited(n);
        queue<size_t> to_visit;
        to_visit.push(0);

        while(not to_visit.empty())
        {
            size_t u = to_visit.front(); to_visit.pop();
            visited[u] = true;
            for(auto v : graph[u])
                if(not visited[v])
                    visited[v] = true, distance[v] = distance[u] + 1, to_visit.push(v);
        }

        return distance;
    }

    size_t solve(size_t n, vector<pair<size_t, size_t>> edges)
    {
        const size_t m = edges.size();

        auto make_graph = [&](size_t t) {
            vector<vector<size_t>> graph(n);
            for(size_t i = 0; i < m; i++) if(i != t)
            {
                size_t u = edges[i].first, v = edges[i].second;
                graph[u].push_back(v);
                graph[v].push_back(u);
            }
            return graph;
        };

        auto base_distance = distances(make_graph(m));

        size_t result = 0;
        for(size_t t = 0; t < m; t++)
            if(base_distance == distances(make_graph(t)))
                result++;

        return result;
    }
}

namespace model
{
    size_t solve(size_t n, vector<pair<size_t, size_t>> edges)
    {
        size_t m = edges.size();
        vector<vector<size_t>> graph(n);
        for(size_t i = 0; i < m; i++)
        {
            size_t u = edges[i].first, v = edges[i].second;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        vector<size_t> requests(n), distance(n);
        vector<bool> visited(n);
        queue<size_t> to_visit;
        to_visit.push(0);

        size_t result = 0, result2 = 0;
        while(not to_visit.empty())
        {
            size_t u = to_visit.front(); to_visit.pop();
            if(requests[u] > 1)
                result += requests[u];
            visited[u] = true;
            for(auto v : graph[u])
            {
                if(not visited[v])
                {
                    if(not requests[v])
                        distance[v] = distance[u] + 1, to_visit.push(v);
                    if(distance[v] == distance[u] + 1)
                        requests[v]++;
                }
                if(distance[u] == distance[v])
                    result2++;
            }
        }

        size_t unvisited_edges = 0;
        for(size_t u = 0; u < n; u++)
            if(not visited[u])
                unvisited_edges += graph[u].size();

        return result + result2/2 + unvisited_edges/2;
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    mt19937 gen(time(0));
    auto randint = [&](size_t lo, size_t hi) {
        return uniform_int_distribution<size_t>{lo, hi}(gen);
    };

    size_t TT = 0;
    while(true)
    {
        cout << TT++ << endl;
        size_t n, m;
        n = randint(2, 10);
        m = randint(1, 30);
        vector<pair<size_t, size_t>> edges(m);
        for(size_t i = 0; i < m; i++)
        {
            size_t u, v;
            //cin >> u >> v; u--; v--;
            u = randint(0, n - 2);
            v = randint(u + 1, n - 1);
            edges[i] = {u, v};
        }

        auto R = brute::solve(n, edges), r = model::solve(n, edges);

        if(R != r)
        {
            cout << "!@# " << R << " " << r << endl;
            cout << edges << endl;
            break;
        }
    }
}
