#include <bits/stdc++.h>

using namespace std;

const size_t MAX_N = 1 << 10, MAX_M = 1 << 9;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static uint64_t A[MAX_N], B[MAX_N];
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i] >> B[i];
    static uint64_t C[MAX_M];
    for(uint32_t w = 1; w <= m; w++)
    {
        C[w] = UINT64_MAX;
        for(uint32_t i = 0; i < n; i++)
            C[w] = min(C[w], A[i] * uint64_t(w) + B[i]);
        for(uint32_t u = 1, v = w - u; u < w; u++, v--)
            C[w] = min(C[w], C[u] + C[v]);
    }
    static uint32_t P[MAX_M];
    for(uint32_t i = 1; i <= m; i++)
        cin >> P[i];
if(m <= 15)
{
    static uint64_t Q[1 << 15];
    Q[0] = UINT64_MAX;
    for(uint32_t i = 1; i < (1u << m); i++)
    {
        uint32_t l = -1u, r = 0;
        for(uint32_t j = 0; j < m; j++)
        {
            if(i & (1u << j))
                l = min(l, P[j+1]), r = max(r, j+1);
        }
        if(l >= r)
            Q[i] = C[__builtin_popcount(i)];
        else
            Q[i] = UINT64_MAX;
    }
    static uint64_t R[1 << 15];
    for(uint32_t i = 1; i < (1u << m); i++)
    {
        R[i] = UINT64_MAX;
        uint32_t j = 0;
        do {
            j = (j - i) & i;
            if(Q[j] != UINT64_MAX)
                R[i] = min(R[i], R[i^j] + Q[j]);
        } while(i != j);
    }
    cout << R[(1<<m)-1];
}
else
{
    uint64_t R = 0;
    static bitset<MAX_M> assigned;
    uint32_t to_assign = m;
    // While any vertex in graph
    while(to_assign)
    {
        //cout << "Left: { ";
        //for(uint32_t i = 1; i <= m; i++) if(not assigned[i])
        //    cout << i << "; ";
        //cout << "}" << endl;
        // Find max clique
        static uint32_t Q[MAX_M][MAX_M], L[MAX_M];
        fill(&Q[0][0], &Q[m+1][0], 0u);
        fill(L, L + (m+1), -1u);
        for(uint32_t i = 1; i <= m; i++)
        {
            if(assigned[i]) continue;
            for(uint32_t p = i; p <= m; p++)
              for(uint32_t g = 0; g < i; g++)
            {
                if(assigned[g]) continue;
                uint32_t pt = min(P[i], p);
                if(Q[pt][i] < Q[p][g] + 1)
                {
                    Q[pt][i] = Q[p][g] + 1;
                    L[i] = g;
                }
            }
        }
        uint32_t max_clique = 0, max_clique_last = -1u;
        for(uint32_t i = 1; i <= m; i++)
        {
            for(uint32_t p = 1; p <= m; p++)
                if(Q[p][i] >= max_clique)
                    max_clique = Q[p][i], max_clique_last = i;
        }
        //cout << "Max clique: " << max_clique << endl;
        // Add cost for clique
        R += C[max_clique];
        // and remove it from the graph
        while(max_clique_last+1 > 1)
        {
            //cout << max_clique_last << "; ";
            assigned[max_clique_last] = true;
            max_clique_last = L[max_clique_last];
            to_assign--;
        }
        //cout << endl;
    }
    cout << R;
}
}
