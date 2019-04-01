#include <vector>
#include <cstdint>
#include <iostream>

using namespace std;

const size_t MAX = 312;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m, k;
    cin >> n >> m >> k;
    static vector<uint32_t> ingoing[MAX], outgoing[MAX];
    auto add_edge = [&](uint32_t u, uint32_t v) {
        outgoing[u].push_back(v);
        ingoing[v].push_back(u);
    };
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v;
        add_edge(u, v);
    }
    uint32_t max_d = n+1;

    static uint32_t Q[MAX][5][MAX];
    fill(&Q[0][0][0], &Q[MAX][0][0], -1u);
    for(uint32_t l = 0; l <= k; l++)
        for(uint32_t d = 0; d <= max_d; d++)
            Q[0][l][d] = 0;

    uint32_t result = 0;
    for(uint32_t i = 1; i <= n; i++)
    {
        uint32_t r = -1u;
        for(uint32_t l = 0; l <= k; l++)
        {
            if(l < k and i != n+1)
            {
                Q[i][l][0] = 0;
                for(uint32_t j : ingoing[i])
                {
                    uint32_t q = -1u;
                    for(uint32_t d = 0; d <= max_d; d++)
                        q = min(q, Q[j][l+1][d]);
                    Q[i][l][0] = max(Q[i][l][0], q);
                }
            }
            for(uint32_t d = 1; d <= max_d; d++)
            {
                Q[i][l][d] = min(d, Q[i][l][d-1]);
                for(uint32_t j : ingoing[i])
                    Q[i][l][d] = max(Q[i][l][d], Q[j][l][d-1]);
            }
        }
        result = max(result, r);
    }

    cout << result << "\n";
}
