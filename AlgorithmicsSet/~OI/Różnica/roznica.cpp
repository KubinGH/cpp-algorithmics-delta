#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 20, MAX_A = 26;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static int32_t R[MAX_A][MAX_A][3];
    int32_t r = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        char c; cin >> c;
        uint32_t a = c - 'a';
        for(uint32_t b = 0; b < MAX_A; b++)
        {
            R[b][a][1]++;
            if(R[b][a][1] > 1 and R[b][a][2])
                R[b][a][1]--, R[b][a][2] = 0;
            if(R[b][a][0] + 1 <= R[b][a][1])
                R[b][a][0] = 0, R[b][a][1] = 1;
            if(R[b][a][0] == 0 and R[b][a][1] == 1)
                R[b][a][2] = 1;
            if(R[b][a][1])
                r = max(r, R[b][a][0] - R[b][a][1]);
            R[a][b][0]++;
            if(R[a][b][1])
                r = max(r, R[a][b][0] - R[a][b][1]);
        }
        //cout << i << endl;
        //for(uint32_t i = 0; i < 2; i++) for(uint32_t j = 0; j < 2; j++)
        //    cout << i << ":" << j << " -> " << R[i][j][0] << " " << R[i][j][1] << " " << R[i][j][2] << endl;
    }
    cout <<  r;
}
