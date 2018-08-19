#include <bits/stdc++.h>

using namespace std;

int main()
{
    static uint32_t C[2][3][26];
    for(uint32_t y = 0; y < 6; y++)
    {
        for(uint32_t x = 0; x < 9; x++)
        {
            char c;
            cin >> c;
            C[0][y/2][c - 'A']++;
            C[1][x/3][c - 'A']++;
        }
    }
    uint32_t r = 0;
    for(uint32_t t = 0; t < 2; t++)
    {
        for(uint32_t a = 0; a < 26; a++)
         for(uint32_t b = 0; b < 26; b++)
          for(uint32_t c = 0; c < 26; c++)
        {
            if(a == b or b == c)
                continue;
            r = max(C[t][0][a] + C[t][1][b] + C[t][2][c], r);
            if(r == C[t][0][a] + C[t][1][b] + C[t][2][c])
                cout << t << ": " << char('A' + a) << " " << char('A' + b) << " " << char('A' + c) << " (" << r << ")" << endl;
        }
    }
    cout << 54 - r;
}
