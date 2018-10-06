#include <bits/stdc++.h>

using namespace std;


// 1, 4, 9, 31, 88, 288
int main()
{
    uint32_t N, M;
    cin >> N >> M;
    static uint32_t A[5042][5042], V[5042][5042];
    A[0][0] = 1;
    for(uint32_t lo = 0; lo <= N; lo++)
        V[0][lo] = 1;
    for(uint32_t n = 1; n <= N; n++)
    {
        if(n < 2) for(uint32_t lo = 1; lo <= N; lo++)
            A[n][lo] = V[n-1][lo-1], V[n][lo] = (V[n][lo-1] + A[n][lo]) % M;
        else
        {
            uint32_t w = A[n-2][0];
            for(uint32_t lo = 1; lo <= N; lo++)
            {
                A[n][lo] = (V[n-1][lo-1] + w) % M;
                w += V[n-2][lo]; w %= M;
                V[n][lo] = (V[n][lo-1] + A[n][lo]) % M;
            }
        }
    }
    uint32_t r = 0;
    for(uint32_t lo = 0; lo <= N; lo++)
        r += A[N][lo], r %= M;
    cout << r;
}
