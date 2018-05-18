#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e6;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static vector<uint32_t> G[MAX];
    uint32_t r = 2;
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
        r = max(G[u].size(), r);
        r = max(G[v].size(), r);
    }
    cout << r + 1;
}
