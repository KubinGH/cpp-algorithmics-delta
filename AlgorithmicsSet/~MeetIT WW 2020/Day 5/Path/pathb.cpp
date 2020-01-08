#include <bits/stdc++.h>

using namespace std;

const uint64_t Mod = 1e9 + 7;

// v - visited vertices
// s - count of vertices on cycle with 1 (path has to end here)
uint64_t solve(uint N, uint v, int s, uint m)
{
    if(m == 0)
        return s == N;
    else
    {
        auto r =
            (v < N ? (N - v) * solve(N, v + 1, s, m - 1) : 0) // visit new vertex
          + (v - s) * solve(N, v, s, m - 1) // go to visited (not source)
          + s * solve(N, v, v, m - 1) // go to source (-> make more sources)
        ;
        return r;
    }
}

uint64_t solve(uint n, uint m)
{
    return solve(n, 1, 1, m);
}

int main()
{
    uint n, m;
    cin >> n >> m;

    static uint A[2][512][512];
    for(size_t v = n+1; v --> 1; )
    {
        const size_t curr = v%2, prev = 1-curr;
        for(size_t s = 0; s < 512; s++)
            for(size_t k = 0; k < 512; k++)
                A[curr][s][k] = 0;
        A[curr][n][0] = 1;
        for(size_t s = v+1; s --> 1; )
        {
            for(size_t k = 1; k <= m; k++)
            {
                A[curr][s][k] = (
                    uint64_t(n - v) * A[prev][s][k-1]
                  + uint64_t(v - s) * A[curr][s][k-1]
                  + uint64_t(s) * A[curr][v][k-1]
                ) % Mod;
            }
        }
    }
    cout << A[1][1][m];
    if(n+m < 15)
        cout << endl << solve(n, m);
}
