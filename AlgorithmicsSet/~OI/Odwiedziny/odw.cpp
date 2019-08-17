#include <bits/stdc++.h>
#include <ktl/util/make_vector.cpp>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<int> cost(n + 1);
    for(size_t i = 1; i <= n; i++)
        cin >> cost[i];

    vector<vector<size_t>> graph(n + 1);
    for(size_t i = 0; i < n - 1; i++)
    {
        size_t u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    const size_t logn = __lg(n), t = min((size_t)floor(sqrt(n * logn)), n);

    // jump[u][k][e] is the vertex k * 2^e closer to root than u

    auto jump = make_vector<size_t>(n + 1, logn + 1);
    auto sum_to_root = make_vector<int>(n + 1);

    vector<size_t> tree_order; tree_order.reserve(n);
    vector<size_t> depth(n + 1);
    depth[0] = -1;
    function<void(size_t, size_t)> dfs = [&](size_t u, size_t parent) {
        tree_order.push_back(u);
        depth[u] = depth[parent] + 1;
        jump[u][0] = parent;
        sum_to_root[u] = sum_to_root[parent] + cost[u];
        for(size_t e = 1; e <= logn; e++)
            jump[u][e] = jump[jump[u][e-1]][e-1];
        for(auto v : graph[u]) if(v != parent)
            dfs(v, u);
    };
    dfs(1, 0);

    vector<size_t> order(n), leap(n - 1);
    for(size_t i = 0; i < n; i++)
        cin >> order[i];
    for(size_t i = 0; i < n - 1; i++)
        cin >> leap[i];

    auto jump_k = make_vector<size_t>(n + 1, logn + 1);
    auto sum_to_root_k = make_vector<int>(n + 1);

    auto kleap = [&](size_t u, size_t k) {
        for(size_t e = logn+1; e --> 0; )
            if(k >= (1u << e))
                 k -= (1 << e), u = jump[u][e];
        return u;
    };
    auto lca = [&](size_t u, size_t v) {
        if(depth[u] > depth[v])
            swap(u, v);
        v = kleap(v, depth[v] - depth[u]);
        if(u == v) return u;
        for(size_t e = logn+1; e --> 0; )
            if(jump[u][e] != jump[v][e])
                u = jump[u][e], v = jump[v][e];
        return jump[u][0];
    };
    auto kstep = [&](size_t u, size_t target, size_t k) {
        int result = 0;
        while(u and depth[u] > depth[target])
        {
            result += cost[u];
            u = kleap(u, k);
        }
        return result;
    };

    jump_k = jump;
    sum_to_root_k = sum_to_root;

    vector<int> answer(n - 1);
    vector<tuple<size_t, size_t, size_t, size_t>> queries(n - 1);
    for(size_t i = 0; i < n - 1; i++)
        queries[i] = make_tuple(leap[i], order[i], order[i+1], i);

    sort(queries.begin(), queries.end());

    size_t curr_k = 1;
    for(auto q : queries)
    {
        size_t k, u, v, i;
        tie(k, u, v, i) = q;

        if(k <= t) while(curr_k < k)
        {
            for(auto w : tree_order)
            {
                jump_k[w][0] = jump[jump_k[w][0]][0];
                sum_to_root_k[w] = sum_to_root_k[jump_k[w][0]] + cost[w];
            }
            curr_k++;
        }

        auto a = lca(u, v);
        int result = 0;
        size_t lu = k - (depth[u] - depth[a]) % k, lv = k - (depth[v] - depth[a]) % k;
        if(k <= t)
        {
            result += sum_to_root_k[u] - sum_to_root_k[kleap(a, lu)];
            result += sum_to_root_k[v] - sum_to_root_k[kleap(a, lv)];

            if(lu == k and lv == k)
                result -= cost[a];
        }
        else
        {
            result += kstep(u, a, k);
            result += kstep(v, a, k);
            if(lu == k and lv == k)
                result += cost[a];
        }
        answer[i] = result;
    }

    for(auto a : answer)
        cout << a << '\n';
}
