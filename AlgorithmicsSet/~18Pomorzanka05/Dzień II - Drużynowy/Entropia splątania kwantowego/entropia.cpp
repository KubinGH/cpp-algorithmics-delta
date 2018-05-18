#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e6;

void fast_cut(map<uint32_t, set<uint32_t>> G, uint32_t n)
{
    abort();
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    srand(42);
    uint32_t n, m;
    cin >> n >> m;
    if(m < 10)
    {
        static pair<uint32_t, uint32_t> E[MAX];
        for(uint32_t i = 0; i < m; i++)
            cin >> E[i].first >> E[i].second, E[i].first--, E[i].second--;
        uint32_t r = m;
        for(uint32_t mask = 0; mask < (1u << m); mask++)
        {
            static vector<uint32_t> G[MAX];
            for(uint32_t i = 0; i < n; i++)
                G[i].clear();
            for(uint32_t i = 0; i < m; i++)
            {
                if((1u << i) & mask)
                {
                    G[E[i].first].push_back(E[i].second);
                    G[E[i].second].push_back(E[i].first);
                }
            }
            stack<uint32_t> S;
            static bitset<MAX> V; V.reset();
            S.push(0); V[0] = true;
            uint32_t c = n;
            while(not S.empty())
            {
                uint32_t u = S.top(); S.pop();
                c--;
                for(uint32_t v : G[u])
                {
                    if(not V[v])
                    {
                        V[v] = true;
                        S.push(v);
                    }
                }
            }
            if(c)
                r = min(m - (uint32_t)__builtin_popcount(mask), r);
        }
        cout << r;
    }
    else
    {
        static map<set<uint32_t>> G;
        for(uint32_t i = 0; i < m; i++)
        {
            uint32_t u, v;
            cin >> u >> v;
            G[u].insert(v);
            G[v].insert(u);
        }
        cout << fast_cut(G, n);
    }
}
