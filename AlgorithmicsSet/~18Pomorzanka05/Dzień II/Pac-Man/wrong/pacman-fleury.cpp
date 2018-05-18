#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e4;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static array<set<uint32_t, greater<uint32_t>>, MAX> G;
    static array<set<uint32_t, greater<uint32_t>>, MAX> I;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        G[u].insert(v);
        I[v].insert(u);
    }
    deque<uint32_t> R;
    stack<uint32_t> S;
    S.push(0);
    while(not S.empty())
    {
        uint32_t v = S.top(); S.pop();
        R.push_back(v);
        cout << v+1 << endl;
        while(not I[v].empty())
        {
            uint32_t w = *I[v].begin();
            I[v].erase(I[v].begin());
            S.push(v);
            v = w;
        }
    }
    for(uint32_t u : R)
        cout << u+1 << " ";
}
