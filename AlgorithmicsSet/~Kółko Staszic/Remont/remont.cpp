#include <bits/stdc++.h>

using namespace std;

const uint32_t INF = -1u - 1;

int main()
{
    uint32_t m, n;
    cin >> m >> n;
    vector<uint32_t> A(n), R(m+1, INF);
    R[0] = 0;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    sort(A.rbegin(), A.rend());
    for(uint32_t a = 0; a < n; a++)
    {
        if(m >= A[a]) for(uint32_t i = m - A[a] + 1; i --> 0;)
            R[i+A[a]] = min(R[i+A[a]], R[i] + 1);
    }
    for(uint32_t i = m+1; i --> 0;)
    {
        if(R[i] != INF)
        {
            cout << i << " " << R[i];
            break;
        }
    }
}
