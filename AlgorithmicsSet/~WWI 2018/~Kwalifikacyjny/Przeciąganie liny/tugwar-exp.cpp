#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 20, MAX_N = 3e4;

uint32_t abs_diff(uint32_t a, uint32_t b) { return a>b ? a - b : b - a; }

uint32_t vis[MAX_N];
bool match(uint32_t u)
{

}

int main()
{
    uint32_t n, k;
    cin >> n >> k;
    static uint32_t P[MAX][2], S[MAX];
    for(uint32_t i = 0; i < 2*n; i++)
        cin >> P[i][0] >> P[i][1] >> S[i];
    if(n <= 10)
    {
        for(uint32_t m = 0; m < (1u << (2*n)); m++)
        {
            bitset<MAX> R; R.reset();
            uint32_t Q[2]; Q[0] = Q[1] = 0;
            for(uint32_t i = 0; i < 2*n; i++)
            {
                uint32_t b = (m & (1u << i)) != 0;
                if(R[P[i][b] + b*n])
                    goto after;
                else
                {
                    R[P[i][b] + b*n] = true;
                    Q[b] += S[i];
                }
            }
            if(abs_diff(Q[0], Q[1]) <= k)
            {
                cout << "YES";
                return 0;
            }
        after:;
        }
        cout << "NO";
        return 0;
    }
    else
    {

    }
}
