#include <bits/stdc++.h>

using namespace std;

using graph_t = vector<vector<pair<uint32_t, uint32_t>>>;
using posint_t = map<uint32_t, uint32_t>;

uint32_t find_center(const graph_t& G)
{
    const uint32_t n = G.size();
    vector<bool> vis(n); vector<uint32_t> deg(n);
    queue<uint32_t> Q;
    for(uint32_t u = 0; u < n; u++)
        deg[u] = G[u].size();
    for(uint32_t u = 0; u < n; u++)
        if(deg[u] == 1)
            Q.push(u), vis[u] = true;
    uint32_t last = -1u;
    while(not Q.empty())
    {
        uint32_t u = Q.front(); Q.pop();
        last = u;
        for(auto e : G[u])
        {
            uint32_t v = e.first;
            if(--deg[v] == 1)
                Q.push(v), vis[v] = true;
        }
        deg[u] = 0;
    }
    return last;
}

bool mapnumber_less(const posint_t& A, const posint_t& B)
{
    return lexicographical_compare(A.rbegin(), A.rend(), B.rbegin(), B.rend());
}

uint32_t dfs_max_depth(const graph_t& G, uint32_t u, uint32_t block = -1u)
{
    uint32_t result = 0;
    for(auto e : G[u]) if(e.first != block)
        result = max(result, dfs_max_depth(G, e.first, u));
    return result + 1;
}

void dfs_map(const graph_t& G, posint_t& T, uint32_t u, uint32_t max_depth, uint32_t block = -1u, uint32_t depth = 0)
{
    for(auto e : G[u]) if(e.first != block)
    {
        uint32_t v, w; tie(v, w) = e;
        dfs_map(G, T, v, max_depth, u, depth + 1);
    }
    if(G[u].size() == 1 and G[u][0].first == block)
        T[depth]++;
}
posint_t get_map(const graph_t& G, uint32_t u, uint32_t block = -1u)
{
    posint_t T;
    dfs_map(G, T, u, dfs_max_depth(G, u, block), block);
    auto it = T.begin(), itx = T.begin();
    for(it = T.begin(); it != T.end(); ++it)
        if(it->second >= 10)
            T[it->first+1] += (it->second / 10), it->second %= 10;
    for(it = T.begin(), itx = ++T.begin(); it != T.end(); it = itx, ++itx)
        if(it->second == 0)
            T.erase(it);
    return T;
}

pair<bool, uint32_t> neighbours_min(const graph_t& G, uint32_t u)
{
    posint_t best; uint32_t b = -1u;
    for(auto e : G[u])
    {
        uint32_t v, w; tie(v, w) = e;
        posint_t curr = get_map(G, v, u);
        if(b == -1u or mapnumber_less(best, curr))
            best.swap(curr), b = v;
    }
    auto x = get_map(G, b, u); auto y = get_map(G, u, b);

    if(mapnumber_less(y, x))
        return {true, b};
    else if(x == y)
        return {false, b};
    else
        return {false, u};
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    graph_t G(n);
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v, w;
        cin >> u >> v >> w; u--; v--;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }

    uint32_t s = find_center(G), z = -1u;

    bool done = false;
    do {
        auto r = neighbours_min(G, s);
        if(not r.first)
        {
            done = true;
            if(r.second != s)
                z = r.second;
        }
        else
            s = r.second;
    } while(not done);

    if(z != -1u)
    {
        if(z < s) swap(s, z);
        cout << "2\n" << s+1 << " " << z+1;
    }
    else
        cout << "1\n" << s+1;
}
