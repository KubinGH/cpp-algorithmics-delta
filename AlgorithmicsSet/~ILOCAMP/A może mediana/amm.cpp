#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

const size_t N = 1024;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static uint32_t A[N][N];
    vector<uint32_t> E, rT(n*n);
    gp_hash_table<uint32_t, uint32_t> T;
    mt19937 gen(42);
    for(uint32_t y = 0; y < n; y++)
        for(uint32_t x = 0; x < n; x++)
            cin >> A[y][x], E.push_back(A[y][x]);
    sort(E.begin(), E.end());
    for(uint32_t i = 0, f = 0; i < n*n; i++)
    {
        if(i and E[i] == E[i-1])
            f++;
        T[E[i]] = i - f;
        rT[i - f] = E[i];
    }
    for(uint32_t y = 0; y < n; y++)
        for(uint32_t x = 0; x < n; x++)
            A[y][x] = T[A[y][x]];
    uint32_t lo = 0, hi = T[E.back()]+1;
    uint32_t s = 2*(n-1);
    while(lo < hi)
    {
        uint32_t mid = (lo + hi) / 2;

        static uint32_t Q[N][N];
        fill(&Q[0][0], &Q[n][0], 0);
        Q[0][0] = (A[0][0] >= mid);
        for(uint32_t i = 1; i < n; i++)
        {
            Q[i][0] = Q[i-1][0] + (A[i][0] >= mid);
            Q[0][i] = Q[0][i-1] + (A[0][i] >= mid);
        }
        for(uint32_t y = 1; y < n; y++)
          for(uint32_t x = 1; x < n; x++)
            Q[y][x] = max(Q[y-1][x], Q[y][x-1]) + (A[y][x] >= mid);

        if(Q[n-1][n-1] <= s/2)
            hi = mid;
        else
            lo = mid+1;
    }
    cout << rT[lo-1];
}
