#include <bits/stdc++.h>

using namespace std;

using graph_t = vector<vector<size_t>>;

struct bipartite_matching
{
    size_t n;
    const graph_t& G;
    vector<bool> vis;

    bipartite_matching(const graph_t& H) : n(H.size()), G(H), vis(n) {}

    bool dfs_match(size_t u, vector<size_t>& match)
    {
        vis[u] = true;
        for(auto v : G[u])
          if(match[v] == SIZE_MAX)
        {
            match[u] = v; match[v] = u;
            return true;
        }

        for(auto v : G[u])
          if(not vis[match[v]] and dfs_match(match[v], match))
        {
            match[u] = v; match[v] = u;
            return true;
        }

        return false;
    }

    vector<size_t> operator() ()
    {
        vector<size_t> match(n, SIZE_MAX);

        bool any = true;
        while(any)
        {
            any = false;
            fill(vis.begin(), vis.end(), false);
            for(size_t u = 0; u < n; u++)
                if(not vis[u] and match[u] == SIZE_MAX)
                    any |= dfs_match(u, match);
        }

        return match;
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    map<string, size_t> yellow;
    vector<string> subs;
    graph_t graph(n);

    for(size_t i = 0; i < n; i++)
    {
        string S;
        cin >> S;
        for(size_t mask = 1; mask < (1u << S.size()); mask++)
          if(__builtin_popcount(mask) <= 4)
        {
            string z; z.reserve(__builtin_popcount(mask));
            for(size_t j = 0; j < S.size(); j++)
                if(mask >> j & 1)
                    z.push_back(S[j]);
            size_t p;
            if(not yellow.count(z))
            {
                p = yellow.size();
                graph.emplace_back();
                subs.push_back(z);
                yellow[z] = p;
            }
            else
                p = yellow[z];
            p += n;
            graph[i].push_back(p);
            graph[p].push_back(i);
        }
    }

    auto match = bipartite_matching{graph}();

    bool ok = true;
    for(size_t i = 0; i < n; i++)
        if(match[i] == SIZE_MAX)
            ok = false;

    if(not ok)
        cout << "-1\n";
    else
        for(size_t i = 0; i < n; i++)
            cout << subs[match[i] - n] << '\n';
}
