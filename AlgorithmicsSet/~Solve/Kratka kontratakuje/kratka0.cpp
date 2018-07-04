#include <bits/stdc++.h>

using namespace std;

const uint32_t MAX = 20, F22 = 28657;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t h, w;
    cin >> h >> w;
    static uint32_t A[MAX][MAX];
    for(uint32_t j = 0; j < h; j++)
        for(uint32_t i = 0; i < w; i++)
            cin >> A[i][j];
    vector<uint32_t> masks;
    for(uint32_t i = 0; i < (1u << h); i++)
    {
        bool ok = true;
        for(uint32_t j = 0; j < h-1 and ok; j++)
            if((i & (1u << j)) and (i & (1u << (j+1))))
                ok = false;
        if(ok)
            masks.push_back(i);
    }
    static uint32_t S[MAX][F22];
    for(uint32_t i = 0; i < w; i++)
    {
        for(uint32_t m = 0; m < masks.size(); m++)
        {
            for(uint32_t j = 0; j < h; j++)
                if(masks[m] & (1u << j))
                    S[i][m] += A[i][j];
        }
    }
    static uint32_t R[MAX][F22];
    for(uint32_t m = 0; m < masks.size(); m++)
        R[0][m] = S[0][m];
    for(uint32_t i = 1; i < w; i++)
    {
        for(uint32_t m = 0; m < masks.size(); m++)
        {
            for(uint32_t m1 = 0; m1 < masks.size(); m1++)
            {
                if((masks[m] & masks[m1]) == 0)
                    R[i][m] = max(R[i][m], S[i][m] + R[i-1][m1]);
            }
        }
    }
    uint32_t r = 0;
    for(uint32_t m = 0; m < masks.size(); m++)
        r = max(r, R[w-1][m]);
    cout << r;
}
