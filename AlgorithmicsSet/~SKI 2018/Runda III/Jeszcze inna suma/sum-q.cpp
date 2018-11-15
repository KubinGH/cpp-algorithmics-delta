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
    vector<int64_t> R((n+1)*(n+1));
    auto I = [n](uint32_t x, uint32_t y) { return x*(n+1) + y; };
    R[I(0, 0)] = 0;
    for(uint32_t k = 1; k <= n; k++)
        R[I(0, k)] = INT64_MIN;
    for(uint32_t i = 1; i <= n; i++)
    {
        for(uint32_t k = 1; k <= n; k++)
            R[I(i, k)] = max(R[I(i-1, k)], R[I(i-1, k-1)] + k * A[i-1]);
    }
    for(uint32_t k = 1; k <= n; k++)
        cout << R[I(n, k)] << " ";
}
