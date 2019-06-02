#include <bits/stdc++.h>

using namespace std;

const size_t NAX = 1e5, oo = -1;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n, m;
    cin >> n >> m;
    vector<vector<size_t>> graph(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<bool> vis(n), flag(n);
    stack<size_t, vector<size_t>> tovis;
    vector<size_t> values;
    size_t base = 0, value_sum = 0;
    for(size_t s = 0; s < n; s++)
    {
        if(vis[s])
            continue;
        flag[s] = true; vis[s] =  true; tovis.push(s);
        size_t c[2] = {0, 0};
        while(not tovis.empty())
        {
            size_t u = tovis.top(); tovis.pop();
            c[flag[u]]++;
            for(size_t v : graph[u])
                if(not vis[v])
                    flag[v] = not flag[u], vis[v] = true, tovis.push(v);
        }
        if(c[0] > c[1])
            swap(c[0], c[1]);
        if(c[0] != c[1])
            values.emplace_back(c[1] - c[0]), value_sum += values.back();
        base += c[0];
    }

    vector<bool> B(n);
    B[0] = true;
    if(not values.empty())
    {
        sort(values.begin(), values.end());
        vector<pair<size_t, size_t>> cvalues = {{0, 0}};
        for(auto v : values)
        {
            if(cvalues.back().first != v)
                cvalues.emplace_back(v, 0);
            cvalues.back().second++;
        }
        vector<vector<size_t>> K(cvalues.size(), vector<size_t>(n, oo));
        K[0][0] = 0;
        for(size_t i = 1; i < cvalues.size(); i++)
        {
            size_t v, c, c1 = cvalues[i-1].second;
            tie(v, c) = cvalues[i];
            for(size_t w = 0; w < n; w++)
            {
                if(K[i-1][w] <= c1)
                    K[i][w] = 0;
                else if(w >= v and K[i][w-v] != oo)
                    K[i][w] = K[i][w-v] + 1;
                else
                    K[i][w] = oo;
            }
        }
        for(size_t w = 0; w < n; w++)
            B[w] = K.back()[w] <= cvalues.back().second;
    }

    uint64_t result = 0;
    for(size_t i = 0; i < n; i++) if(B[i])
    {
        size_t x = base+i, y = base+(value_sum-i);
        uint64_t r = (uint64_t) x * y - m;
        result = max(result, r);
    }

    cout << result;
}
