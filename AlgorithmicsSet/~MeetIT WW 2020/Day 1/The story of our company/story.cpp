#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

vector<uint> A;
vector<vector<bool>> G;
vector<bool> vis;

void dfs(size_t u, const vector<size_t>& V, bool toggle, vector<size_t>& out)
{
    if(vis[u]) return;
    vis[u] = true;
    for(auto v : V)
        if(G[u][v] ^ toggle)
            dfs(v, V, toggle, out);
    out.push_back(u);
}

vector<vector<size_t>> components(const vector<size_t>& V, bool toggle)
{
    fill(vis.begin(), vis.end(), true);
    for(auto u : V)
        vis[u] = false;
    vector<vector<size_t>> ret;
    for(auto s : V)
    {
        if(vis[s])
            continue;
        ret.emplace_back();
        dfs(s, V, toggle, ret.back());
        sort(ret.back().begin(), ret.back().end());
    }
    return ret;
}

pair<uint, vector<size_t>> max_indset(const vector<size_t>& V, bool toggle);

pair<uint, vector<size_t>> max_clique(const vector<size_t>& V, bool toggle)
{
    if(V.empty())
        return {0, {}};
    else if(V.size() == 1)
        return {A[V[0]], V};
    auto C = components(V, toggle);
    if(C.size() > 1)
    {
        pair<uint, vector<size_t>> r = {0, {}};
        for(const auto& c : C)
            r = max(r, max_clique(c, toggle));
        return r;
    }
    else
        return max_indset(V, not toggle);
}

pair<uint, vector<size_t>> max_indset(const vector<size_t>& V, bool toggle)
{
    if(V.empty())
        return {0, {}};
    else if(V.size() == 1)
        return {A[V[0]], V};
    auto C = components(V, toggle);
    if(C.size() > 1)
    {
        pair<uint, vector<size_t>> r = {0, {}};
        for(const auto& c : C)
        {
            auto sub = max_indset(c, toggle);
            r.first += sub.first;
            copy(sub.second.begin(), sub.second.end(), back_inserter(r.second));
        }
        sort(r.second.begin(), r.second.end());
        return r;
    }
    else
        return max_clique(V, not toggle);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    A.resize(n); G.resize(n); vis.resize(n);

    for(auto& x : A) cin >> x;

    for(size_t u = 0; u < n; u++)
        G[u].resize(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        G[u][v] = G[v][u] = true;
    }

    vector<size_t> V;
    for(size_t u = 0; u < n; u++)
        V.push_back(u);

    auto [result, clique] = max_clique(V, false);
    cout << result << '\n' << clique.size() << '\n';
    for(auto u : clique)
        cout << u+1 << ' ';
}
