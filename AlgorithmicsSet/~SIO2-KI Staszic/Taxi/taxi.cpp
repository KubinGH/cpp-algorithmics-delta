#include <bits/stdc++.h>

using namespace std;

int d(pair<int, int> a, pair<int, int> b)
{
    return abs(a.first - b.first) + abs(a.second - b.second);
}

const size_t nul = SIZE_MAX;
struct bipartite_matching
{
    const vector<vector<size_t>>& graph;
    vector<bool> vis;
    vector<size_t> match;

    bipartite_matching(const vector<vector<size_t>>& g)
        : graph(g), vis(g.size(), true), match(g.size(), nul) {}

    bool rematch(size_t u)
    {
        vis[u] = true;
        for(auto v : graph[u])
            if(match[v] == nul)
                { match[v] = u; match[u] = v; return true; }
        for(auto v : graph[u])
            if(not vis[match[v]] and rematch(match[v]))
                { match[v] = u; match[u] = v; return true; }
        return false;
    }

    vector<size_t> operator() ()
    {
        fill(match.begin(), match.end(), nul);
        bool any = true;
        while(any)
        {
            fill(vis.begin(), vis.end(), false);
            any = false;
            for(size_t u = 0; u < graph.size(); u++)
                if(match[u] == nul and not vis[u])
                    any |= rematch(u);
        }
        return match;
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<int> when(n), len(n);
    vector<pair<int, int>> start(n), end(n);
    for(size_t i = 0; i < n; i++)
    {
        string S;
        cin >> S >> start[i].first >> start[i].second >> end[i].first >> end[i].second;
        when[i] = 60*((S[0]-'0')*10 + (S[1]-'0')) + ((S[3]-'0')*10 + (S[4]-'0'));
    }

    vector<vector<size_t>> graph(2*n);
    for(size_t i = 0; i < n; i++)
      for(size_t j = 0; j < n; j++)
    {
        if(when[i] + d(start[i], end[i]) + d(end[i], start[j]) < when[j])
            graph[i].push_back(j+n), graph[j+n].push_back(i);
    }

    auto match = bipartite_matching{graph}();

    cout << count(match.begin(), match.end(), nul)/2 << endl;
}
