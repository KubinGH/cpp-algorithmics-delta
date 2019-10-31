#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int64_t oo = INT64_MAX / 3;

template<typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

vector<int64_t> sssp(const vector<vector<pair<size_t, int64_t>>> graph, size_t src)
{
    const size_t n = graph.size();
    vector<bool> lock(n);
    vector<int64_t> dist(n, +oo);

    min_priority_queue<pair<int64_t, size_t>> Q;

    auto maybe = [&](size_t u, int64_t d) {
        if(d < dist[u])
            Q.emplace(dist[u] = d, u);
    };
    maybe(src, 0);

    while(not Q.empty())
    {
        auto [_, u] = Q.top(); Q.pop();
        if(lock[u]) continue;
        lock[u] = true;

        for(auto [v, w] : graph[u])
            maybe(v, dist[u] + w);
    }

    return dist;
}

vector<size_t> segment_tree_nodes(size_t base, size_t L, size_t R)
{
    vector<size_t> result;
    for(L += base, R += base+1; L < R; L /= 2, R /= 2)
    {
        if(L % 2) result.push_back(L++);
        if(R % 2) result.push_back(--R);
    }
    return result;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, src;
    cin >> n >> m >> src;
    src--;

    const size_t base = 1 << __lg(2*n - 1);

    auto out_tree_vertex = [&](size_t node) {
        return node >= base ? node - base : node + 1*base;
    };
    auto in_tree_vertex = [&](size_t node) {
        return node >= base ? node - base : node + 2*base;
    };

    vector<vector<pair<size_t, int64_t>>> graph(3 * base);
    for(size_t i = 2*base; i --> 2; )
    {
        graph[out_tree_vertex(i)].emplace_back(out_tree_vertex(i / 2), 0);
        graph[in_tree_vertex(i / 2)].emplace_back(in_tree_vertex(i), 0);
    }

    while(m --> 0)
    {
        size_t a1, a2, b1, b2; int64_t w;
        size_t t;
        cin >> t;
        if(t == 1) {
            cin >> a1 >> b1;
            a2 = a1; b2 = b1;
        } else if(t == 2) {
            cin >> a1 >> b1 >> b2;
            a2 = a1;
        } else if(t == 3) {
            cin >> b1 >> a1 >> a2;
            b2 = b1;
        }
        cin >> w;
        a1--; a2--; b1--; b2--;
        for(auto a : segment_tree_nodes(base, a1, a2))
            for(auto b : segment_tree_nodes(base, b1, b2))
                graph[out_tree_vertex(a)].emplace_back(in_tree_vertex(b), w);
    }


    auto dist = sssp(graph, src);
    dist.resize(n);
    for(auto d : dist)
        cout << (d == +oo ? -1 : d) << " ";
}
