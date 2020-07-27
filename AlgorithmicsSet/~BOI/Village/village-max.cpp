#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 17;

vector<size_t> graph[MAX];
size_t n, parent[MAX], sz[MAX], depth[MAX], ss[MAX];

size_t subtree_size(size_t u, size_t v)
{
    auto re = parent[v] == u ? sz[v] : n - sz[u];
    return re;
}

void dfs(size_t u)
{
    sz[u] = 1;
    for(auto v : graph[u])
        if(v != parent[u])
            parent[v] = u, depth[v] = depth[u] + 1, dfs(v), sz[u] += sz[v];
}

size_t find_centroid(size_t u)
{
    while(true)
    {
        bool any = false;
        for(auto v : graph[u])
          if(subtree_size(u, v) > subtree_size(v, u))
        {
            u = v;
            any = true;
            break;
        }
        if(not any)
            break;
    }
    return u;
}

void dfs2(size_t u, vector<size_t>& ord, size_t s)
{
    ord.push_back(u);
    ss[u] = s;
    for(auto v : graph[u])
        if(v != parent[u])
            dfs2(v, ord, s);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    cin >> n;

    for(size_t i = 0; i < n - 1; i++)
    {
        size_t u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1);
    auto cen = find_centroid(1);

    fill(parent, parent + MAX, 0);
    fill(sz, sz + MAX, 0);
    fill(depth, depth + MAX, 0);
    dfs(cen);

    vector<vector<size_t>> groups;
    for(auto u : graph[cen])
    {
        vector<size_t> curr;
        dfs2(u, curr, u);
        groups.push_back(curr);
    }

    vector<size_t> to(n+1);
    size_t last = cen, m = n;

    auto cmp = [](const auto& lhs, const auto& rhs) {
        return lhs->size() > rhs->size() or (lhs->size() == rhs->size() and lhs < rhs);
    };

    set<vector<size_t>*, decltype(cmp)> st(cmp);
    for(auto& g : groups)
        st.insert(&g);

    vector<size_t>* over = nullptr;
    auto init = last;
    while(m > 1)
    {
        auto& g = **st.begin(); st.erase(st.begin());

        to[last] = g.back();
        g.pop_back();
        last = to[last];

        if(over)
            st.insert(over);
        over = &g;

        m--;
    }
    to[last] = init;

    uint64_t result = 0;
    for(size_t u = 1; u <= n; u++)
        result += depth[u] + depth[to[u]], assert(ss[u] != ss[to[u]]);

    cout << result << endl;
    for(size_t u = 1; u <= n; u++)
        cout << to[u] << ' ';
    cout << endl;
}
