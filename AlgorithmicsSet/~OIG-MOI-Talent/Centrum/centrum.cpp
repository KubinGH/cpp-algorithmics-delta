#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 4096;

static vector<uint32_t> graph[MAX];

void dfs_distcounter(uint32_t u, uint32_t* arr, uint32_t imp, uint32_t d)
{
    arr[d]++;
    for(uint32_t v : graph[u])
        if(v != imp)
            dfs_distcounter(v, arr, u, d + 1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    // global vector<uint32_t> graph[MAX];
    vector<pair<uint32_t, uint32_t>> edges; edges.reserve(n - 1);
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        edges.emplace_back(u, v);
    }
    uint32_t result = 0;
    for(auto e : edges)
    {
        uint32_t us, vs; tie(us, vs) = e;
        static uint32_t A[MAX], B[MAX];
        fill(A, A + n, 0); fill(B, B + n, 0);
        dfs_distcounter(us, A, vs, 0);
        dfs_distcounter(vs, B, us, 0);
        static uint32_t S[MAX], Z[MAX];
        partial_sum(A, A + n, S);
        partial_sum(B, B + n, Z);
        for(uint32_t l = 0, r = k; l <= k; l++, r--)
            result = max(result, S[l] + Z[r]);
    }
    cout << result;
}
