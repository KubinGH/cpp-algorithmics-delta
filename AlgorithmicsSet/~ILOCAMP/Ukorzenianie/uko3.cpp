#include <bits/stdc++.h>

using namespace std;

const size_t N = 1 << 7;

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
    static bitset<N> A; A.set();
    for(uint32_t f : F)
    {
        static bitset<N> C;
        for(uint32_t s = 0; s < 2; s++)
        {
            C.set();
            for(uint32_t u : W[s][f])
            {
                static bitset<N> V; V.reset();
                stack<uint32_t> S; S.push(u); V[u] = true;
                while(not S.empty())
                {
                    uint32_t v = S.top(); S.pop();
                    for(auto e : G[v])
                        if((e.g != f or (e.g == f and e.s == s)) and not V[e.v])
                            S.push(e.v), V[e.v] = true;
                }
                C &= V;
            }
            if(C.any())
                break;
        }
        A &= C;
    }
    for(uint32_t i = 0; i < n; i++)
    {
        if(A[i])
        {
            cout << i+1;
            break;
        }
    }
}
