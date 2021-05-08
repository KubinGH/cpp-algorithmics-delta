#include <bits/stdc++.h>

using namespace std;

int64_t centroid_decomposition(size_t k, const vector<vector<size_t>>& graph, size_t start, vector<bool>& lock)
{
    if(not k)
        return 0;
    vector<size_t> vertices;
    static vector<size_t> sub; sub.resize(graph.size());
    function<void(size_t, size_t)> dfs = [&](size_t u, size_t parent) {
        sub[u] = 1;
        for(auto v : graph[u])
            if(v != parent and not lock[v])
                dfs(v, u), sub[u] += sub[v];
        vertices.push_back(u);
    };
    dfs(start, 0);

    size_t centroid = start;
    for(auto u : vertices)
        if(sub[u] >= (vertices.size()+1)/2 and sub[u] <= sub[centroid])
            centroid = u;

    int64_t result = 0; {
        vector<int> cnt(1), cnt_all(1);
        cnt_all[0] = 1;

        function<size_t(size_t, size_t, size_t)> dfs_paths = [&](size_t u, size_t d, size_t parent) {
            size_t l = d;
            while(cnt.size() <= l)
                cnt.push_back(0), cnt_all.push_back(cnt_all.back());
            cnt[d]++;
            if(d < k) for(auto v : graph[u])
                if(v != parent and not lock[v])
                    l = max(l, dfs_paths(v, d + 1, u));
            return l;
        };
        for(auto u : graph[centroid]) if(not lock[u])
        {
            auto l = dfs_paths(u, 1, centroid);
            for(size_t d = 0; d <= l; d++)
                result += (int64_t)cnt[d] * cnt_all[min(k - d, cnt_all.size() - 1)];
            int c = 0;
            for(size_t d = 0; d <= l; d++)
                c += cnt[d], cnt_all[d] += c, cnt[d] = 0;
            for(size_t d = l+1; d < cnt_all.size(); d++)
                cnt_all[d] += c;
        }
    }

    lock[centroid] = true;
    for(auto u : graph[centroid])
        if(not lock[u])
            result += centroid_decomposition(k, graph, u, lock);

    return result;
}

int64_t centroid_decomposition(size_t k, const vector<vector<size_t>>& graph, size_t start)
{
    vector<bool> lock(graph.size());
    return centroid_decomposition(k, graph, start, lock);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, k1, k2;
    cin >> n >> k1 >> k2;

    vector<vector<size_t>> graph(n + 1);
    for(size_t i = 1; i < n; i++)
    {
        size_t u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    cout << centroid_decomposition(k2, graph, 1) - centroid_decomposition(k1 - 1, graph, 1) << endl;
}
