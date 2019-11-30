#include <bits/stdc++.h>
#include <ktl/graph/flow/dinic.cpp>

using namespace std;

int main()
{
    uint32_t a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;

    flow::graph G(8);

    const uint32_t W = 1 << 27;
    vector<tuple<size_t, size_t, uint32_t>> edges = {
        {0, 1, a}, {0, 2, b}, {0, 3, c},
        {1, 4, W}, {1, 6, W},
        {2, 4, W}, {2, 5, W},
        {3, 5, W}, {3, 6, W},
        {4, 7, d}, {5, 7, e}, {6, 7, f}
    };

    for(auto [u, v, w] : edges)
        G[u].push_back({v, w});

    auto [result, G1] = dinic::find_max_flow(G, 0, 7);

    cout << (a+b+c) - result;
}
