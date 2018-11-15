#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<int64_t> A(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    vector<int64_t> R(n+1);
    R[0] = 0;
    for(uint32_t k = 1; k <= n; k++)
        R[k] = INT64_MIN;
    for(uint32_t i = 1; i <= n; i++)
        for(uint32_t k = i+1; k --> 1; )
            R[k] = max(R[k], R[k-1] + k * A[i-1]);
    for(uint32_t k = 1; k <= n; k++)
        cout << R[k] << " ";
}
