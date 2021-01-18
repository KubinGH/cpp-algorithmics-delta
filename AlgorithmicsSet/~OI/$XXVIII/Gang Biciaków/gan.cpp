// Jakub Bachurski
// Gang Biciaków - O(q sqrt(n) + m)

#include <bits/stdc++.h>

using namespace std;

const size_t nul = SIZE_MAX;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, q;
    cin >> n >> m >> q;

    vector<vector<pair<size_t, size_t>>> graph(n);
    vector<size_t> val(n, nul);
    for(size_t i = 1; i < n; i++)
    {
        size_t u, v, x;
        cin >> u >> v >> x; u--; v--; x--;
        graph[u].emplace_back(v, i);
        graph[v].emplace_back(u, i);
        val[i] = x;
    }

    vector<size_t> order, point(n, nul), edge_of(n, nul), parent(n, nul), preorder(n, nul);
    order.reserve(2*n); parent[0] = 0;
    function<void(size_t)> dfs = [&](size_t u) {
        preorder[u] = order.size();
        order.push_back(u);
        for(auto [v, i] : graph[u])
            if(parent[v] == nul)
                point[i] = v, edge_of[v] = i, parent[v] = u, dfs(v);
        order.push_back(u);
    };
    dfs(0);

    vector<size_t> answer;
    vector<tuple<size_t, size_t, size_t>> queries, updates;
    answer.reserve(q); queries.reserve(q); updates.reserve(q);

    for(size_t j = 0; j < q; j++)
    {
        char c;
        cin >> c;

        if(c == 'Z')
        {
            size_t u;
            cin >> u; u--;
            queries.emplace_back(preorder[u] + 1, updates.size(), answer.size());
            answer.push_back(nul);
        }
        else if(c == 'B')
        {
            size_t i, v;
            cin >> i >> v; v--;
            updates.emplace_back(i, v, val[i]);
            val[i] = v;
        }
    }

    vector<bool> on(n), onq(updates.size(), true);
    vector<size_t> cnt(m);

    size_t X = 1, Y = 0, unique = 0;
    auto toggle_vertex = [&](size_t u) {
        if(on[u]) unique -= not --cnt[val[edge_of[u]]];
        else      unique += not cnt[val[edge_of[u]]]++;
        on[u] = not on[u];
    };
    auto toggle_x = [&](size_t x) {
        toggle_vertex(order[x]);
    };
    auto update_val = [&](size_t i, size_t v) {
        if(on[point[i]])
            toggle_vertex(point[i]), val[i] = v, toggle_vertex(point[i]);
        else
            val[i] = v;
    };
    auto toggle_y = [&](size_t y) {
        auto [i, v, w] = updates[y];
        update_val(i, onq[y] ? w : v);
        onq[y] = not onq[y];
    };

    for(size_t i = updates.size(); i --> 0; )
        toggle_y(i);

    const size_t k = updates.empty() ? 1 :
        (size_t) max(1.0, floor(sqrt((double) queries.size()*n / updates.size())));
    sort(queries.begin(), queries.end(), [&](const auto& lhs, const auto& rhs) {
        const auto& [x1, y1, _1] = lhs; const auto& [x2, y2, _2] = rhs;
        if(x1 / k == x2 / k and y1 != y2)
            return (x1/k) & 1 ? y1 > y2 : y1 < y2;
        else
            return x1 < x2;
    });

    int __steps = 0;
    for(auto [x, y, i] : queries)
    {
        while(X < x) toggle_x(X++), __steps++;
        while(X > x) toggle_x(--X), __steps++;
        while(Y < y) toggle_y(Y++), __steps++;
        while(Y > y) toggle_y(--Y), __steps++;

        answer[i] = unique;
    }

    // cerr << "steps = " << __steps << ", expected " << (int)round(q*sqrt(n)) << " / " << max((int)n, (int)round(sqrt(updates.size() * queries.size() * n))) << endl;

    for(auto a : answer)
        cout << a << '\n';
}
