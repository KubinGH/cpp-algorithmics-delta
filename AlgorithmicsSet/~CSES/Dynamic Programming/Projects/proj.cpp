#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    map<int, size_t> remap;
    vector<tuple<int, int, int64_t>> P(n);
    remap[0];
    for(auto& [a, b, w] : P)
        cin >> a >> b >> w, remap[a], remap[b];
    size_t m = 0;
    for(auto& [k, v] : remap)
        v = m++;

    vector<vector<pair<size_t, int64_t>>> graph(m);
    for(auto [a, b, w] : P)
        graph[remap[b]].emplace_back(remap[a] - 1, w);

    vector<int64_t> best(m);
    for(size_t i = 1; i < m; i++)
    {
        best[i] = best[i-1];
        for(auto [j, w] : graph[i])
            best[i] = max(best[i], best[j] + w);
    }

    cout << best.back() << endl;
}
