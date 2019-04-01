#include <bits/stdc++.h>

using namespace std;

uint32_t n;

vector<vector<pair<uint32_t, uint64_t>>> below;

uint64_t result = 0;

pair<uint64_t, uint64_t> median(vector<uint64_t> A)
{
    sort(A.begin(), A.end());
    return make_pair(
           A[(A.size()+1)/2-1],
           accumulate(A.begin() + (A.size()+1)/2, A.end(), 0llu)
           - accumulate(A.begin(), A.begin() + A.size()/2, 0llu));
}

uint64_t dfs_contract(uint32_t u)
{
    if(below[u].empty())
        return 0;
    vector<uint64_t> weights;
    weights.reserve(below[u].size());
    for(auto e : below[u])
    {
        uint32_t v; uint64_t w; tie(v, w) = e;
        w += dfs_contract(v);
        weights.push_back(w);
    }
    auto M = median(weights);
    result += M.second;
    return M.first;
}

int main()
{
    uint32_t n1, n2;
    cin >> n1 >> n2;
    n = n1 + n2;
    below.resize(n);
    for(uint32_t v = 1; v < n; v++)
    {
        uint32_t u, w;
        cin >> u >> w; u--;
        below[u].emplace_back(v, w);
    }
    dfs_contract(0);
    cout << result;
}
