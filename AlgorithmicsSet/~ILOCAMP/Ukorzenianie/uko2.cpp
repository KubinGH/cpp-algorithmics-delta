#include <bits/stdc++.h>

using namespace std;

const size_t N = 1 << 17;

struct edge { uint32_t v, g; bool s; };

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    static vector<edge> G[N];
    static vector<uint32_t> W[2][N];
    vector<uint32_t> F;
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v, g;
        cin >> u >> v >> g; u--; v--; g--;
        G[u].push_back({v, g, 0}); W[0][g].push_back(v);
        G[v].push_back({u, g, 1}); W[1][g].push_back(u);
        F.push_back(g);
    }
    sort(F.begin(), F.end());
    F.erase(unique(F.begin(), F.end()), F.end());
    for(uint32_t r = 0; r < n; r++)
    {
        static bitset<N> K, S, V;
        for(uint32_t i = 0; i < k; i++)
            K[i] = S[i] = false;
        for(uint32_t i = 0; i < n; i++)
            V[i] = false;
        stack<uint32_t> T;
        T.push(r); V[r] = true;
        uint32_t z = 0;
        while(not T.empty())
        {
            z++;
            uint32_t u = T.top(); T.pop();
            for(auto e : G[u])
            {
                if(not V[e.v])
                {
                    if(K[e.g] and S[e.g] != e.s)
                        continue;
                    K[e.g] = true;
                    S[e.g] = e.s;
                    V[e.v] = true;
                    T.push(e.v);
                }
            }
        }
        if(z == n)
        {
            cout << r+1;
            break;
        }
    }
}
