#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

const size_t MAX = 1000000;

uint64_t pairs(uint32_t n)
{
    return (n * (n - 1)) / 2;
}

int main()
{
    uint32_t n;
    scanf("%u", &n);
    static vector<uint32_t> G[MAX];
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        scanf("%u %u", &u, &v); u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    static uint32_t P[MAX];
    static vector<uint32_t> D[MAX];
    static pair<uint32_t, uint32_t> E[MAX]; uint32_t ei = 0;
    static bitset<MAX> V;
    queue<uint32_t> Q;
    Q.push(0); V[0] = true;
    vector<uint32_t> L;
    while(not Q.empty())
    {
        uint32_t u = Q.front(); Q.pop();
        bool any = false;
        for(uint32_t i = 0; i < G[u].size(); i++)
        {
            uint32_t v = G[u][i];
            if(not V[v])
            {
                V[v] = true;
                P[v] = u;
                D[u].push_back(v);
                E[ei].first = u; E[ei].second = v; ei++;
                any = true;
                Q.push(v);
            }
        }
        if(not any)
            L.push_back(u);
    }
    cerr << "leaves: ";
    for(uint32_t u : L)
        cerr << u+1 << ", "; cerr << endl;
    static uint32_t C[MAX];
    V.reset();
    for(uint32_t i = 0; i < L.size(); i++)
        Q.push(L[i]), V[L[i]] = true;
    V[0] = true;
    while(not Q.empty())
    {
        uint32_t u = Q.front(); Q.pop();
        C[P[u]] += C[u] + 1;
        if(not V[P[u]])
            Q.push(P[u]), V[P[u]] = true;
    }
    for(uint32_t i = 0; i < n; i++)
        cerr << i+1 << ": " << C[i] << endl;
    uint64_t result = pairs(n);
}
