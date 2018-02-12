#include <bits/stdc++.h>

using namespace std;

const uint16_t LC = 26;
const size_t MAX = 30000;
const uint32_t LIM = 123456789;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint16_t xn, k;
    cin >> xn >> k;
    static array<array<bool, LC>, LC> B;
    for(uint16_t i = 0; i < k; i++)
    {
        char a, b; cin >> a >> b; a -= 'a'; b -= 'a';
        B[a][b] = true;
    }
    static array<array<uint32_t, LC>, MAX+1> R;
    for(uint16_t i = 0; i < LC; i++)
        R[1][i] = 1;
    for(uint16_t n = 2; n <= xn; n++)
    {
        for(uint16_t i = 0; i < LC; i++)
        {
            for(uint16_t j = 0; j < LC; j++)
            {
                if(not B[i][j])
                {
                    R[n][i] += R[n-1][j];
                    if(R[n][i] >= LIM) R[n][i] %= LIM;
                }
            }
        }
    }
    uint32_t r = 0;
    for(uint16_t i = 0; i < LC; i++)
    {
        r += R[xn][i];
        if(r >= LIM) r %= LIM;
    }
    cout << r;
}
