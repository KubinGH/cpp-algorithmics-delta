#include <bits/stdc++.h>

using namespace std;

uint32_t dfs_depth(const vector<vector<uint32_t>>& G, uint32_t u, uint32_t block)
{
    uint32_t r = 0;
    for(uint32_t v : G[u]) if(v != block)
        r = max(r, dfs_depth(G, v, block));
    return r + 1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<uint32_t> F(n);
    vector<vector<uint32_t>> G(n);
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> F[i], F[i]--;
        G[F[i]].push_back(i);
    }
    uint32_t result = 0;
    { // I
        vector<uint32_t> C(n, -1u), P(n, -1u);
        for(uint32_t s = 0; s < n; s++) if(C[s] == -1u)
        {
            if(F[s] == s)
            {
                C[s] = 1;
                continue;
            }
            uint32_t u = s;
            stack<uint32_t> S;
            do {
                P[u] = S.size();
                S.push(u);
                u = F[u];
            } while(C[u] == -1u and P[u] == -1u);
            uint32_t q = u;
            if(C[q] == -1u)
            {
                C[q] = S.size() - P[q];
                do {
                    u = S.top();
                    C[u] = C[q];
                    P[u] = -1u;
                    S.pop();
                } while(S.top() != q);
                P[q] = -1u; S.pop();
            }
            while(not S.empty())
            {
                u = S.top();
                C[u] = 0;
                P[u] = -1u;
                S.pop();
            }
        }
        result = max(result, *max_element(C.begin(), C.end()));
    }
    { // II
        uint32_t c1 = 0;
        vector<bool> V(n);
        for(uint32_t s = 0; s < n; s++) if(not V[s])
        {
            if(s == F[F[s]])
            {
                uint32_t z = F[s]; V[z] = true;
                uint32_t e = dfs_depth(G, s, z), f = dfs_depth(G, z, s);
                c1 += e + f;
            }
        }
        result = max(result, c1);
    }
    cout << result;
}
