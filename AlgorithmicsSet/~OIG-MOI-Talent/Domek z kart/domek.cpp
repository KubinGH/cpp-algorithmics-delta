#include <bits/stdc++.h>

using namespace std;

const size_t MAX_N = 17, MAX_K = 40 / 2;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k; k /= 2;
    static int32_t A[(1u<<MAX_N)-1];
    for(uint32_t i = 0; i < (1u << n) - 1; i++)
    {
        int32_t a, b;
        cin >> a >> b;
        A[i] = a + b;
    }
    static int32_t R[(1u<<MAX_N)-1][MAX_K+1];
    for(uint32_t i = (1u << n) - 1; i --> 0; )
    {
        fill(begin(R[i]), begin(R[i]) + k+1, A[i]);
        R[i][0] = 0;
        if(i < (1u << (n-1)) - 1) // is not leaf
        {
            for(uint32_t u = 0; u <= k; u++)
            {
                for(uint32_t v = 0; v <= k; v++)
                {
                    if(u + v + 1 > k)
                        continue;
                    R[i][u+v+1] = max(
                        R[i][u+v+1],
                        R[2*i+1][u] + R[2*i+2][v] + A[i]
                    );
                }
            }
        }
    }
    cout << *max_element(begin(R[0]), begin(R[0]) + k+1);
}
