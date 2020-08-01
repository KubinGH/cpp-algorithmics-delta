// Note to self:
// overflow detection via __builtin_***_overflow is actually
// not that significant here in comparison to doing the multiplication
// via 64 bits, but it is faster (binary searches are dominant so it's hard to tell).
// Next note:
// Doing the binary search with a 32-bit int isn't that significant either..??

#include <bits/stdc++.h>

using namespace std;

vector<size_t> graph[1 << 20];

int k;
vector<int> M;
int64_t result = 0;

void dfs(size_t u, int a = 1, int b = 0, size_t lock = SIZE_MAX)
{
    if(lock != SIZE_MAX and graph[u].size() == 1)
    {
        if((int64_t)k*a < INT_MAX)
        {
            auto ita = lower_bound(M.begin(), M.end(), k*a);
            auto itb = (int64_t)k*a + b < INT_MAX
                       ? upper_bound(M.begin(), M.end(), k*a + b)
                       : M.end();
           result += itb - ita;
        }
        return;
    }

    for(auto v : graph[u])
      if(v != lock)
    {
        int d = max(graph[v].size() - 1, (size_t)1);
        if((int64_t)d*a < INT_MAX and (int64_t)d*b + d-1 < INT_MAX)
            dfs(v, d*a, d*b + d-1, u);
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q >> k;

    M.resize(q);
    for(auto& m : M)
        cin >> m;
    sort(M.begin(), M.end());

    size_t a, b;
    cin >> a >> b;
    for(size_t i = 1; i < n - 1; i++)
    {
        size_t u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    graph[a].push_back(n+1);
    graph[n+1].push_back(a);
    graph[b].push_back(n+2);
    graph[n+2].push_back(b);

    dfs(n+1);
    dfs(n+2);

    cout << result * k << endl;
}
