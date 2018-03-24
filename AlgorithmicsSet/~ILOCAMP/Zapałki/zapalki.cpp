#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e6;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> A, R, L;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        if(i > 0 and A[i] >= A[i-1])
            R[i] = R[i-1];
        R[i]++;
    }
    for(uint32_t i = n; i --> 0; )
    {
        if(i < n - 1 and A[i] >= A[i+1])
            L[i] = L[i+1];
        L[i]++;
    }
    uint32_t r = 0;
    for(uint32_t i = 0; i < n; i++)
        r = max(r, L[i] + R[i] - 1);
    cout << r;
}
