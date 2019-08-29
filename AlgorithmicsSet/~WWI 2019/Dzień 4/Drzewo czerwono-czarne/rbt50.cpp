#include <bits/stdc++.h>
#include <ktl/util/extio.cpp>
#define for_each_child(__name) for(auto __name : graph[u]) if(__name != jump[u][0])

using namespace std;

template<typename T>
struct divalue
{
    T a[2];
    T& operator[] (size_t i) { return a[i]; }
    const T& operator[] (size_t i) const { return a[i]; }
    friend divalue operator+ (const divalue& a, const divalue& b)
    {
        return {a[0] + b[0], a[1] + b[1]};
    }
    divalue operator- () const { return {-a[0], -a[1]}; }
    friend divalue operator- (const divalue& a, const divalue& b)
    {
        return a + (-b);
    }
#define INPLACE_OP(__op, __iop) \
friend divalue operator __iop (divalue& a, const divalue& b) \
{ \
    return a = a __op b; \
}
    INPLACE_OP(+, +=)
    INPLACE_OP(-, -=)
#undef INPLACE_OP
    friend ostream& operator<< (ostream& out, const divalue& v)
    {
        return out << "[" << v[0] << ", " << v[1] << "]";
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    vector<bool> color(n+1);
    for(size_t i = 1; i <= n; i++)
    {
        char c;
        cin >> c;
        color[i] = (c == '1');
    }

    vector<vector<size_t>> graph(n + 1);
    for(size_t i = 0; i < n - 1; i++)
    {
        size_t a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> depth(n + 1);
    vector<vector<size_t>> jump(n + 1);
    vector<size_t> topo; topo.reserve(n);

    function<void(size_t)> dfs_root = [&](size_t u) {
        for_each_child(v)
        {
            depth[v] = depth[u] + 1;
            jump[v].push_back(u);
            for(size_t e = 1; (1 << e) <= depth[v]; e++)
                jump[v].push_back(jump[jump[v][e-1]][e-1]);
            dfs_root(v);
        }
        topo.push_back(u);
    };

    jump[1].push_back(0);
    dfs_root(1);

    auto lca = [&](size_t u, size_t v) {
        if(depth[u] > depth[v])
            swap(u, v);
        for(size_t e = jump[v].size(); e --> 0; )
            if(depth[v] >= depth[u] + (1 << e))
                v = jump[v][e];
        if(u == v)
            return v;
        assert(jump[u].size() == jump[v].size());
        for(size_t e = jump[v].size(); e --> 0; )
        {
            if(e < jump[v].size() and jump[u][e] != jump[v][e])
                u = jump[u][e], v = jump[v][e];
        }
        return jump[v][0];
    };

    auto dist = [&](size_t u, size_t v) {
        return depth[u] + depth[v] - 2*depth[lca(u, v)];
    };

    vector<divalue<int64_t>> sub_dist_sum(n + 1), dist_sum(n + 1), sub_count(n + 1);

    auto recompute_sub_dist_sum = [&]() {
        for(auto u : topo)
        {
            sub_count[u] = {0, 0};
            sub_count[u][color[u]]++;
            sub_dist_sum[u] = {0, 0};
            for_each_child(v)
            {
                sub_count[u] += sub_count[v];
                sub_dist_sum[u] += sub_dist_sum[v] + sub_count[v];
            }
        }
    };

    function<void(size_t)> dfs_dist_sum = [&](size_t u) {
        dist_sum[u] = sub_dist_sum[u];
        for_each_child(v)
        {
            auto x = sub_dist_sum[u], y = sub_dist_sum[v];
            auto e = sub_count[u], f = sub_count[v];

            sub_dist_sum[u] -= sub_dist_sum[v] + sub_count[v];
            sub_count[u] -= sub_count[v];
            sub_dist_sum[v] += sub_dist_sum[u] + sub_count[u];
            sub_count[v] += sub_count[u];

            dfs_dist_sum(v);

            sub_dist_sum[u] = x;
            sub_dist_sum[v] = y;
            sub_count[u] = e;
            sub_count[v] = f;
        }
    };

    vector<bool> last_color = color;
    recompute_sub_dist_sum();
    dfs_dist_sum(1);

    //const size_t k = (int)floor(sqrt(n / max((int)__lg(n), 1)));
    const size_t k = floor(sqrt(n));


    vector<pair<size_t, bool>> backlog;
    backlog.reserve(k + 3);

    vector<bool> considered(n + 1);

    for(size_t t = 1; t <= q; t++)
    {
        size_t type, u;
        cin >> type >> u;
        if(type == 1)
            backlog.emplace_back(u, color[u] = not color[u]);
        else if(type == 2)
        {
            int64_t result = dist_sum[u][color[u]];
            cout << color << " " << last_color << endl;
            for(size_t i = backlog.size(); i --> 0; )
            {
                auto p = backlog[i];
                size_t v = p.first;
                if(considered[v])
                    continue;
                int d = dist(u, v);
                if(color[v] != last_color[v])
                {
                    if(color[v] != color[u])
                        result -= d;
                    else
                        result += d;
                }
                considered[v] = true;
            }
            for(auto p : backlog)
                considered[p.first] = false;
            cout << result << '\n';
        }
        if(backlog.size() > k)
        {
            recompute_sub_dist_sum();
            dfs_dist_sum(1);
            backlog.clear();
            last_color = color;
        }
    }
}
