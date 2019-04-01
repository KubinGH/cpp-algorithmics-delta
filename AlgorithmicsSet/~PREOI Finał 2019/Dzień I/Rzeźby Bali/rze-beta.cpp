#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, a, b;
    cin >> n >> a >> b;
    vector<uint64_t> Y(n), S(n+1);
    for(uint32_t i = 0; i < n; i++)
        cin >> Y[i], S[i+1] = S[i] + Y[i];

    if(a > 1)
    {
        uint64_t pattern = -1llu;
        for(uint32_t k = 64; k --> 0; )
        {
            pattern ^= (1llu << k);
            bool any = false;
            vector<vector<bool>> cando(n+1, vector<bool>(n+1));
            cando[0][0] = true;
            for(uint32_t x = 1; x <= n and not any; x++)
            {
                for(uint32_t i = x; i <= n; i++)
                    for(uint32_t j = x-1; j < i and not cando[x][i]; j++)
                        if(cando[x-1][j] and ((S[i]-S[j]) | pattern) == pattern)
                            cando[x][i] = true;
                if(a <= x and x <= b and cando[x][n])
                    any = true;
            }
            if(not any)
                pattern ^= (1llu << k);
        }
        cout << pattern;
    }
    else
    {
        uint64_t pattern = -1llu;
        for(uint32_t k = 64; k --> 0; )
        {
            pattern ^= (1llu << k);
            vector<uint32_t> cando(n+1, -1u);
            cando[0] = 0;
            for(uint32_t i = 1; i <= n; i++)
                for(uint32_t j = 0; j < i; j++)
                    if(cando[j] != -1u and ((S[i]-S[j]) | pattern) == pattern)
                        cando[i] = min(cando[i], cando[j] + 1);
            if(cando[n] > b)
                pattern ^= (1llu << k);
        }
        cout << pattern;
    }
}
