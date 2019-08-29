#include <bits/stdc++.h>

using namespace std;

struct bipartite_matching
{
    using graph_t = vector<array<size_t, 3>>;

    const graph_t& graph;
    size_t n;
    vector<bool> vis;
    vector<size_t> match;

    bipartite_matching(const graph_t& _graph)
        : graph(_graph), n(graph.size()), vis(n), match(n, SIZE_MAX) {}

    bool dfs_match(size_t u)
    {
        vis[u] = true;
        for(auto v : graph[u]) if(v)
        {
            if(match[v] == SIZE_MAX)
            {
                match[u] = v; match[v] = u;
                return true;
            }
        }
        for(auto v : graph[u]) if(v)
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
            for(size_t u = 1; u < n; u++)
                if(match[u] == SIZE_MAX and dfs_match(u))
                    any = true;
        }
        return match;
    }
};


const size_t NAX = 3333;

int main()
{
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

    static size_t down[NAX][NAX], right[NAX][NAX];
    vector<array<size_t, 3>> graph;
    graph.reserve(w*h);

    auto rgt = [&](size_t x, size_t y) {
        return x+2 < w and A[y][x] == 'R' and A[y][x+1] == 'G' and A[y][x+2] == 'W';
    };
    auto dwn = [&](size_t x, size_t y) {
        return y+2 < h and A[y][x] == 'R' and A[y+1][x] == 'G' and A[y+2][x] == 'W';
    };

    graph.emplace_back();
    for(size_t y = 0; y < h; y++)
      for(size_t x = 0; x < w; x++)
    {
        if(rgt(x, y))
        {
            right[y][x] = graph.size();
            graph.emplace_back();
        }
        if(dwn(x, y))
        {
            down[y][x] = graph.size();
            graph.emplace_back();
        }
    }
    for(size_t y = 0; y < h; y++)
      for(size_t x = 0; x < w; x++)
    {
        size_t i = down[y][x], j = right[y][x];
        if(i)
        {
            if(j)                           graph[i][0] = (j);
            if(x>0 and right[y+1][x-1])     graph[i][1] = (right[y+1][x-1]);
            if(x>1 and right[y+2][x-2])     graph[i][2] = (right[y+2][x-2]);
        }
        if(j)
        {
            if(i)                           graph[j][0] = (i);
            if(y>0 and down[y-1][x+1])      graph[j][1] = (down[y-1][x+1]);
            if(y>1 and down[y-2][x+2])      graph[j][2] = (down[y-2][x+2]);
        }
    }


    const size_t n = graph.size() - 1;

    auto match = bipartite_matching{graph}();

    uint result = 2*n;
    for(size_t i = 1; i <= n; i++)
        if(match[i] != SIZE_MAX)
            result--;

    printf("%u", result / 2);
}
