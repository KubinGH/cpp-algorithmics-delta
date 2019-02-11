#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<vector<uint32_t>> graph(n);
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<uint32_t> order; order.reserve(n);
    vector<vector<uint32_t>> children(n);
    stack<uint32_t> tovis;
    vector<bool> vis(n);
    tovis.push(0); vis[0] = true;
    while(not tovis.empty())
    {
        uint32_t u = tovis.top(); tovis.pop();
        for(uint32_t v : graph[u]) if(not vis[v])
        {
            children[u].push_back(v);
            vis[v] = true;
            tovis.push(v);
        }
        order.push_back(u);
    }
    reverse(order.begin(), order.end());
    vector<array<uint32_t, 2>> Z(n, {-1u, -1u});
    for(uint32_t u : order)
    {
        auto& ch = children[u];
        if(ch.size() >= 2)
        {

            uint32_t z_a = 1;
            for(uint32_t v : ch)
                z_a += Z[v][1];
            Z[u][0] = min(Z[u][0], z_a);

            auto cmp = [&](uint32_t a, uint32_t b) {
                return make_pair(Z[a][0]-Z[a][1], a) < make_pair(Z[b][0]-Z[b][1], b);
            };
            auto it1 = min_element(ch.begin(), ch.end(), cmp);
            iter_swap(it1, ch.begin());
            auto it2 = min_element(ch.begin()+1, ch.end(), cmp);
            iter_swap(it2, ch.begin()+1);

            uint32_t z_b = z_a - 1 + (Z[ch[0]][0]-Z[ch[0]][1])
                                   + (Z[ch[1]][0]-Z[ch[1]][1]);
            Z[u][0] = min(Z[u][0], z_b);

            uint32_t z_c = z_a - 1 + (Z[ch[0]][0]-Z[ch[0]][1]);

            Z[u][1] = min(Z[u][0], z_c);
        }
        else if(ch.size() == 1)
        {
            uint32_t v = ch[0];
            Z[u][0] = Z[v][1] + 1;
            Z[u][1] = min(Z[v][0], Z[v][1] + 1);
        }
        else
            Z[u][0] = Z[u][1] = 1;
    }
    cout << Z[0][0];
}
