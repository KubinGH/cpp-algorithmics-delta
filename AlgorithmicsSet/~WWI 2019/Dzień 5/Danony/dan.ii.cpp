#include <bits/stdc++.h>

// -*- ktl/graph/bipartite_matching.cpp -*-

#include <vector>
#include <cstddef>
#include <cstdint>

using std::vector; using std::size_t;

struct bipartite_matching
{
    using graph_t = vector<vector<size_t>>;

    const graph_t& graph;
    size_t n;
    vector<bool> vis;
    vector<size_t> match;

    bipartite_matching(const graph_t& _graph)
        : graph(_graph), n(graph.size()), vis(n), match(n, SIZE_MAX) {}

    bool dfs_match(size_t u)
    {
        vis[u] = true;
        for(auto v : graph[u])
        {
            if(match[v] == SIZE_MAX)
            {
                match[u] = v; match[v] = u;
                return true;
            }
        }
        for(auto v : graph[u])
        {
            if(not vis[match[v]] and dfs_match(match[v]))
            {
                match[u] = v; match[v] = u;
                return true;
            }
        }
        return false;
    }

    vector<size_t> operator() ()
    {
        fill(match.begin(), match.end(), SIZE_MAX);

        bool any = true;
        while(any)
        {
            any = false;
            fill(vis.begin(), vis.end(), false);
            for(size_t u = 0; u < n; u++)
                if(match[u] == SIZE_MAX and dfs_match(u))
                    any = true;
        }
        return match;
    }
};

// -$- ktl/graph/bipartite_matching.cpp -$-


using namespace std;

const size_t NAX = 3333;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    uint h_, w_;
    scanf("%u %u\n", &h_, &w_);
    size_t h = h_, w = w_;

    static char A[NAX][NAX];
    for(size_t y = 0; y < h; y++)
    {
        for(size_t x = 0; x < w; x++)
            A[y][x] = getchar_unlocked();
        getchar_unlocked();
    }

    static vector<size_t> here[NAX][NAX];

    size_t n = 0;
    for(size_t y = 0; y < h; y++)
      for(size_t x = 0; x < w; x++)
    {
        if(x+2 < w and A[y][x] == 'R' and A[y][x+1] == 'G' and A[y][x+2] == 'W')
        {
            here[y][x].push_back(n);
            here[y][x+1].push_back(n);
            here[y][x+2].push_back(n);
            n++;
        }
        if(y+2 < h and A[y][x] == 'R' and A[y+1][x] == 'G' and A[y+2][x] == 'W')
        {
            here[y][x].push_back(n);
            here[y+1][x].push_back(n);
            here[y+2][x].push_back(n);
            n++;
        }
    }

    vector<vector<size_t>> graph(n);

    for(size_t y = 0; y < h; y++)
      for(size_t x = 0; x < w; x++)
        for(auto u : here[y][x])
          for(auto v : here[y][x])
            if(u != v)
              graph[u].push_back(v);

    auto match = bipartite_matching{graph}();

    size_t result = 2*n;
    for(size_t i = 0; i < n; i++)
        if(match[i] != SIZE_MAX)
            result--;

    cout << result / 2;
}
