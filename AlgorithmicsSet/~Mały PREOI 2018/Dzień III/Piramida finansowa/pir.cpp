#include <bits/stdc++.h>

using namespace std;

typedef pair<uint32_t, uint32_t> pair_u32;

uint32_t n;
vector<uint32_t> parent, result, subtree_size, depth;
vector<vector<uint32_t>> children;

void dfs_preprocess(uint32_t u)
{
    subtree_size[u] = 1;
    for(uint32_t v : children[u])
    {
        depth[v] = depth[u] + 1;
        dfs_preprocess(v);
        subtree_size[u] += subtree_size[v];
    }
}

deque<pair_u32> process(uint32_t u)
{
    if(children[u].empty())
    {
        result[u] = 0;
        return {{depth[u], 1}};
    }
    for(uint32_t i = 0; i < children[u].size(); i++)
    {
        if(subtree_size[children[u][i]] > subtree_size[children[u][0]])
            swap(children[u][0], children[u][i]);
    }
    deque<pair_u32> U = process(children[u][0]);
    result[u] = 0;
    if(U[result[children[u][0]]].second > 1)
        result[u] = result[children[u][0]]+1;
    U.emplace_front(depth[u], 1);
    for(uint32_t i = 1; i < children[u].size(); i++)
    {
        deque<pair_u32> V = process(children[u][i]);
        while(V.back().first > U.back().first)
            U.emplace_back(U.back().first+1, 0);
        for(auto p : V)
        {
            uint32_t t = p.first - depth[u];
            U[t].second += p.second;
            if(U[t].second > U[result[u]].second
               or (U[t].second == U[result[u]].second and t < result[u]))
                result[u] = t;
        }
    }
    return U;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    parent.resize(n); children.resize(n);
    for(uint32_t i = 1; i < n; i++)
    {
        cin >> parent[i], parent[i]--;
        children[parent[i]].push_back(i);
    }
    subtree_size.resize(n); depth.resize(n);
    dfs_preprocess(0);
    result.resize(n);
    process(0);
    for(uint32_t i = 0; i < n; i++)
        cout << result[i] << "\n";
}
