#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000, JUMP_POINTERS = 17;

uint32_t lca(const array<array<uint32_t, JUMP_POINTERS>, MAX>& J,
             const array<uint32_t, MAX>& D,
             uint32_t u, uint32_t v)
{
    if(D[u] < D[v])
        swap(u, v);
    for(uint32_t i = JUMP_POINTERS; i --> 0;)
        if(J[u][i] != -1u and D[J[u][i]] >= D[v])
            u = J[u][i];
    if(u == v)
        return u;
    for(uint32_t i = JUMP_POINTERS; i --> 0;)
    {
        if(J[u][i] != J[v][i] and J[u][i] != -1u)
            u = J[u][i], v = J[v][i];
    }
    return J[u][0];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<vector<uint32_t>, MAX> G;
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        G[u].push_back(v); G[v].push_back(u);
    }
    static array<uint32_t, MAX> P, D;
    static array<array<uint32_t, JUMP_POINTERS>, MAX> J;
    for(uint32_t i = 0; i < MAX; i++)
        J[i].fill(-1u);
    static array<bool, MAX> V;
    queue<uint32_t> Q;
    Q.push(0); V[0] = true;
    while(not Q.empty())
    {
        uint32_t u = Q.front(); Q.pop();
        for(uint32_t v : G[u])
        {
            if(not V[v])
            {
                P[v] = u;
                J[v][0] = u;
                for(uint32_t i = 1; i < JUMP_POINTERS; i++)
                {
                    uint32_t x = J[v][i-1];
                    if(x == -1u) break;
                    J[v][i] = J[x][i-1];
                }
                D[v] = D[u] + 1;
                Q.push(v);
                V[v] = true;
            }
        }
    }
    uint32_t q;
    cin >> q;
    for(uint32_t qi = 0; qi < q; qi++)
    {
        uint32_t u, v, w;
        cin >> u >> v >> w; u--; v--; w--;
        uint32_t a = lca(J, D, u, v);
        if(a == w)
        {
            cout << "TAK\n";
            continue;
        }
        for(uint32_t i = JUMP_POINTERS; i --> 0;)
        {
            if(J[u][i] != -1u and D[J[u][i]] >= D[w])
                u = J[u][i];
            if(J[v][i] != -1u and D[J[v][i]] >= D[w])
                v = J[v][i];
        }
        if((u == w or v == w) and D[a] <= D[w])
            cout << "TAK\n";
        else
            cout << "NIE\n";
    }
}
