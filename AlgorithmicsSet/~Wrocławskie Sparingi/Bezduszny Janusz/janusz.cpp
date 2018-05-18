#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e5;
const uint32_t LIM = 1e9;

void bfs_distances(const array<vector<uint32_t>, MAX>& G, uint32_t s,
                   array<uint32_t, MAX>& R)
{
    R.fill(-1u);
    static bitset<MAX> V; V.reset();
    queue<uint32_t> Q;
    V[s] = true;
    Q.push(s);
    R[s] = 0;
    while(not Q.empty())
    {
        uint32_t u = Q.front(); Q.pop();
        for(uint32_t v : G[u])
        {
            if(not V[v])
            {
                V[v] = true;
                Q.push(v);
                R[v] = R[u] + 1;
            }
        }
    }
}

uint32_t viva_la_revolucion(uint32_t n)
{
    uint32_t r = 0;
    while(n)
    {
        r *= 10;
        r += n % 10;
        n /= 10;
    }
    return r;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static uint32_t A[MAX];
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i], A[i] %= LIM;
    uint32_t m;
    cin >> m;
    static array<vector<uint32_t>, MAX> G;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    static array<uint32_t, MAX> D[2];
    bfs_distances(G, 0, D[0]);
    bfs_distances(G, n-1, D[1]);
    uint32_t q;
    cin >> q;
    for(uint32_t i = 0; i < q; i++)
    {
        uint32_t u, d;
        cin >> u >> d; u--;
        if(u == 0 or u == n - 1)
            A[u] = (A[u] + d) % LIM;
        if(D[0][u] <= d)
            A[0]   = viva_la_revolucion(A[0]) % LIM;
        if(D[1][u] <= d)
            A[n-1] = viva_la_revolucion(A[n-1]) % LIM;
        if(A[0] < A[n-1])
            cout << 1 << "\n";
        else
            cout << n-1 << "\n";
    }
}
