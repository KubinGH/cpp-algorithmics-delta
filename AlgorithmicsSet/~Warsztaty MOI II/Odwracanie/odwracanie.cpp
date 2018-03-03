#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    static array<bitset<MAX>, MAX> G;
    for(uint32_t u = 0; u < n; u++)
        G[u].set();
    set<uint32_t> S;
    for(uint32_t i = 0; i < k; i++)
    {
        char c; uint32_t u;
        cin >> c >> u; u--;
        bool t = c == 'A';
        uint32_t f = t + 2 * u;
        if(S.find(f) == S.end())
            S.insert(f);
        else
            S.erase(f);
    }
    for(uint32_t f : S)
    {
        bool t = f % 2; uint32_t u = f / 2;
        if(t)
            G[u].flip();
        else
            for(uint32_t v = 0; v < n; v++)
                G[v][u] = not G[v][u];
    }
    for(uint32_t u = 0; u < n; u++)
    {
        uint32_t c = 0;
        for(uint32_t v = 0; v < n; v++)
            if(u != v)
                c += G[u][v];
        cout << c << " ";
        for(uint32_t v = 0; v < n; v++)
            if(G[u][v] and u != v)
                cout << v+1 << " ";
        cout << '\n';
    }
}
