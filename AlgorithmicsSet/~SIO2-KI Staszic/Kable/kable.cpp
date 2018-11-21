#include <bits/stdc++.h>

using namespace std;

const size_t MAX_N = 512;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, max_k;
    cin >> n >> max_k;
    static uint64_t value[MAX_N][MAX_N], line[MAX_N][MAX_N], cut[MAX_N][MAX_N];
    for(uint32_t i = 0; i < n; i++)
    {
        for(uint32_t j = i+1; j < n; j++)
            cin >> value[i][j];
        for(uint32_t j = n; j --> i+1; )
            line[i][j] = line[i][j+1] + value[i][j];
    }
    for(uint32_t i = 0; i < n; i++)
      for(uint32_t j = i+1; j < n; j++)
        for(uint32_t k = i; k < j; k++)
          cut[i][j] += line[k][j];
    static uint64_t Q[2][MAX_N][MAX_N];
    static bitset<MAX_N>* S[2][MAX_N][MAX_N];
    bitset<MAX_N> emptyset;
    for(uint32_t i = 0; i < n; i++) for(uint32_t c = 0; c <= i; c++)
        S[0][c][i] = &emptyset;
    for(uint32_t k = 1; k <= max_k; k++)
    {
        uint32_t k1 = k%2, k0 = 1-k1;
        fill(&Q[k1][0][0], &Q[k1][n+1][0], 0);
        for(uint32_t i = 0; i < n; i++) for(uint32_t c = 0; c <= i; c++)
            S[k1][c][i] = &emptyset;
        for(uint32_t i = 0; i < n; i++)
        {
            uint32_t c_r = -1u;
            for(uint32_t c = 0; c < i; c++)
            {
                uint64_t q_c = Q[k0][c][i-1] + cut[c][i];
                if(q_c > Q[k1][i][i])
                {
                    c_r = c;
                    Q[k1][i][i] = q_c;
                }
                Q[k1][c][i] = Q[k1][c][i-1];
                S[k1][c][i] = S[k1][c][i-1];
            }
            if(c_r != -1u)
            {
                S[k1][i][i] = new bitset<MAX_N>(*S[k0][c_r][i-1]);
                (*S[k1][i][i])[i] = 1;
            }
        }
    }
    uint32_t k1 = max_k%2;
    uint64_t result = 0; uint32_t result_c = -1u;
    for(uint32_t c = 0; c < n; c++)
    {
        uint64_t q = Q[k1][c][n-1];
        if(q > result or result_c == -1u)
            result = q, result_c = c;
    }
    cout << result << "\n";
    for(uint32_t i = 0; i < n; i++)
        if((*S[k1][result_c][n-1])[i])
            cout << i << " ";
}
