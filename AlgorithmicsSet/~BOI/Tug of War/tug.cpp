#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 20 * (1 << 17);

namespace graph
{
    struct edge_t
    {
        size_t u, v;
        int w;
        size_t nd(size_t a) { return u == a ? v : u; }
    };

    size_t n;
    vector<vector<size_t>> inc;
    vector<edge_t> edges;

    struct medusa
    {
        vector<size_t> vertices;
        int base, on_cycle;
    };

    vector<bool> vis;
    void dfs_visit(size_t u, vector<size_t>& out)
    {
        if(vis[u]) return;
        vis[u] = true;
        out.push_back(u);
        for(auto i : inc[u])
            dfs_visit(edges[i].nd(u), out);
    }

    vector<medusa> find_all_medusa()
    {
        vector<medusa> medusi;
        for(size_t u = 0; u < n; u++)
        {
            if(not vis[u])
            {
                medusi.emplace_back();
                auto& V = medusi.back().vertices;
                dfs_visit(u, V);
                size_t s = 0;
                for(auto v : V)
                    s += inc[v].size();
                s /= 2;
                if(s != V.size())
                    return {};
            }
        }


        vector<size_t> deg(n);
        for(auto& e : edges)
            deg[e.u]++, deg[e.v]++;

        fill(vis.begin(), vis.end(), false);
        auto cut = vis;

        for(auto& m : medusi)
        {
            queue<size_t> Q;
            for(auto u : m.vertices)
                if(deg[u] == 1)
                    Q.push(u);

            size_t cut_count = 0;
            int curr = 0;

            auto cycle_switch = [&]() {
                if(Q.empty() and cut_count < m.vertices.size())
                {
                    m.base = curr; curr = 0;
                    for(auto u : m.vertices)
                      if(not cut[u])
                    {
                        Q.push(u);
                        return true;
                    }
                }
                return false;
            };

            while(not Q.empty() or cycle_switch())
            {
                auto u = Q.front(); Q.pop();
                cut[u] = true;
                cut_count++;
                for(auto i : inc[u])
                {
                    auto v = edges[i].nd(u);
                    if(not vis[i])
                    {
                        --deg[u];
                        if(--deg[v] == 1)
                            Q.push(v);
                        vis[i] = true;
                        curr += edges[i].w * (u < n/2 ? 1 : -1);
                        break;
                    }
                }
            }
            m.on_cycle = abs(curr);
        }

        return medusi;
    }
}

vector<bool> solve_knapsack(vector<int> items, int hi = INT_MAX)
{
    if(items.empty()) return {true};

    sort(items.begin(), items.end());
    vector<pair<int, int>> citems;
    citems.emplace_back(items.front(), 0);
    for(auto x : items)
        if(citems.back().first == x)
            citems.back().second++;
        else
            citems.emplace_back(x, 1);

    int n = min(accumulate(items.begin(), items.end(), 1), hi);
    static array<bool, MAX> knapsack;

    knapsack[0] = true;
    for(auto p : citems)
    {
        auto w = p.first, c = p.second;
        for(int x = n; x --> 0; )
            if(knapsack[x])
                for(int i = 1; i <= c and x + w*i < n and not knapsack[x + w*i]; i++)
                    knapsack[x + w*i] = true;
    }

    vector<bool> out;
    copy(knapsack.begin(), knapsack.end(), back_inserter(out));
    return out;
}

int main()
{
    size_t n; int k;
    cin >> n >> k;

    graph::n = 2*n;
    graph::inc.resize(2*n); graph::edges.resize(2*n); graph::vis.resize(2*n);

    for(size_t i = 0; i < 2*n; i++)
    {
        auto& e = graph::edges[i];
        cin >> e.u >> e.v >> e.w;
        e.u--; e.v--; e.v += n;
        graph::inc[e.u].push_back(i);
        graph::inc[e.v].push_back(i);
    }

    auto medusi = graph::find_all_medusa();

    if(medusi.empty())
    {
        cout << "NO" << endl;
        return 0;
    }

    vector<int> items;
    int base = 0;
    for(auto& m : medusi)
    {
        int a = m.base - m.on_cycle, b = m.base + m.on_cycle; // a or b
        items.push_back(b - a); // 0 or b - a
        base += a;
    }


    int lo = -k - base, hi = +k - base;
    auto knapsack = solve_knapsack(items, hi + 1);

    bool cando = false;
    for(int x = lo; x <= hi; x++)
        if(0 <= x and x < (int)knapsack.size() and knapsack[x])
            cando = true;

    cout << (cando ? "YES" : "NO") << endl;
    return 0;
}
