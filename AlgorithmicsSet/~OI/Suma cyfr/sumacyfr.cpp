#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 201;
const uint64_t MAX_I = (1llu << 60);

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t s, m, q;
    cin >> s >> m >> q;
    static uint32_t pow10[MAX];
    static uint64_t DP[MAX][MAX][MAX];
    static bool inf[MAX][MAX][MAX];
    DP[0][0][0] = 1;
    pow10[0] = 1 % m;
    for(uint32_t i = 0; i < MAX - 1; i++)
    {
        for(uint32_t j = 0; j <= s; j++)
          for(uint32_t k = 0; k < m; k++)
        {
            for(uint32_t d = 0; d < 10; d++)
            {
                if(j + d <= s)
                {
                    uint32_t fi = i+1, fj = j+d, fk = (k + d*pow10[i]) % m;
                    DP[fi][fj][fk] += DP[i][j][k];
                    if(inf[i][j][k] or DP[fi][fj][fk] > MAX_I)
                    {
                        inf[fi][fj][fk] = true;
                        DP[fi][fj][fk] = min(DP[fi][fj][fk], (1llu << 62));
                    }
                }
            }
        }
        pow10[i+1] = (pow10[i] * 10) % m;
    }
    while(q --> 0)
    {
        uint64_t w;
        cin >> w;
        uint32_t i;
        uint64_t b = 0;
        i = MAX - (inf[MAX-1][s][0] or DP[MAX-1][s][0] >= w);
        if(i < MAX)
        {
            uint32_t j = s, k = 0;
            bool z = false;
            while(i)
            {
                uint64_t b = 0;
                for(uint32_t d = 0; d < 10; d++)
                {
                    uint32_t pi = i-1, pj = j-d, pk = (256*m + k - pow10[i-1]*d) % m;
                    if(inf[pi][pj][pk] or DP[pi][pj][pk] >= w - b)
                    {
                        i = pi; j = pj; k = pk;
                        w -= b;
                        if(d) z = true;
                        if(z) cout << d;
                        break;
                    }
                    else
                        b += DP[pi][pj][pk];
                }
            }
            cout << "\n";
        }
        else
            cout << "NIE\n";
    }

}
