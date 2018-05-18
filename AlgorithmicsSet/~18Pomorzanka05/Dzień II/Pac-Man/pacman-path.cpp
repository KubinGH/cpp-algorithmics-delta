#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e4;

void dfs_euler(array<multiset<uint32_t>, MAX>& G, uint32_t u, stack<uint32_t>& R)
{
    while(not G[u].empty())
    {
        uint32_t v = *G[u].begin();
        G[u].erase(G[u].begin());
        dfs_euler(G, v, R);
    }
    R.push(u);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static array<multiset<uint32_t>, MAX> G;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        G[u].insert(v);
    }
    stack<uint32_t> R;
    dfs_euler(G, 0, R);
    while(not R.empty())
    {
        cout << R.top()+1 << " "; R.pop();
    }
}
