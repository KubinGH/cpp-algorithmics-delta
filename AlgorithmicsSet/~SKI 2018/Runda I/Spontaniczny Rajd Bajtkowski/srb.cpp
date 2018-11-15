#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 17;
const uint64_t oo = 1llu<<61;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static vector<uint32_t> G[MAX];
    static uint32_t U[MAX], V[MAX];
    static uint64_t W[MAX];
    for(uint32_t i = 0; i < m; i++)
    {
        cin >> U[i] >> V[i] >> W[i];
        U[i]--; V[i]--;
        G[U[i]].push_back(i);
        G[V[i]].push_back(i);
    }
    static uint64_t P[MAX][2][2];
    fill(&P[0][0][0], &P[n+1][0][0], oo);
    for(uint32_t r = 0; r < 2; r++)
    {
        uint32_t s = r ? (n-1) : 0;
        using dij_dt = pair<uint64_t, uint32_t>;
        priority_queue<dij_dt, vector<dij_dt>, greater<dij_dt>> Q;
        P[s][r][0] = 0;
        Q.emplace(0, s);
        while(not Q.empty())
        {
            uint64_t c; uint32_t u;
            tie(c, u) = Q.top(); Q.pop();
            if(c <= P[u][r][1]) for(uint32_t e : G[u])
            {
                uint32_t v = (U[e]==u ? V[e] : U[e]);
                uint64_t p[2] = {P[u][r][0] + W[e], P[u][r][1] + W[e]};
                if(p[0] < P[v][r][0])
                {
                    if(P[v][r][0] < P[v][r][1])
                        P[v][r][1] = P[v][r][0];
                    Q.emplace(P[v][r][0] = p[0], v);
                }
                if(P[v][r][0] < p[0] and p[0] < P[v][r][1])
                    Q.emplace(P[v][r][1] = p[0], v);
                if(P[v][r][0] < p[1] and p[1] < P[v][r][1])
                    Q.emplace(P[v][r][1] = p[1], v);
            }
        }
    }
    uint64_t A = P[n-1][0][0], B = oo;
    static bool I[MAX];
    vector<uint32_t> S;
    S.reserve(n);
    for(uint32_t i = 0; i < m; i++)
      for(uint32_t r = 0; r < 2; r++)
        for(uint32_t x = 0; x < 2; x++)
          for(uint32_t y = 0; y < 2; y++)
    {
        uint64_t d = W[i] + P[U[i]][r][x] + P[V[i]][!r][y];
        if(A < d and d < B)
        {
            B = d;
            for(uint32_t j : S)
                I[j] = false;
            S.clear();
        }
        if(d == B and not I[i])
        {
            S.push_back(i);
            I[i] = true;
        }
    }
    sort(S.begin(), S.end());
    cout << S.size() << "\n";
    for(uint32_t e : S)
        cout << e+1 << " ";
}
