#include <bits/stdc++.h>

using namespace std;

int main()
{
    uint32_t n, m;
    cin >> n >> m;
    vector<vector<uint32_t>> below(n);
    vector<uint32_t> W(n), V(n);
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t b;
        cin >> b >> W[i] >> V[i];
        if(i > 0)
            below[b-1].push_back(i);
    }
    function<void(uint32_t, vector<uint32_t>&)> dfs_weights = [&](uint32_t u, vector<uint32_t>& out) {
        for(uint32_t v : below[u])
            dfs_weights(v, out);
        out.push_back(W[u]);
    };
    vector<uint32_t> w; w.reserve(n);
    uint64_t result = 0;
    for(uint32_t u = 0; u < n; u++)
    {
        w.clear();
        dfs_weights(u, w);
        sort(w.begin(), w.end());
        partial_sum(w.begin(), w.end(), w.begin());
        uint64_t d = upper_bound(w.begin(), w.end(), m) - w.begin();
        result = max(result, d * V[u]);
    }
    cout << result;
}
