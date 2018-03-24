#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 5000000;

uint32_t max(uint32_t a, uint32_t b)
{
    return a > b ? a : b;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    static array<uint32_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    sort(A.begin(), A.begin() + n);
    uint32_t result = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        result = max(result, upper_bound(A.begin() + i, A.begin() + n, A[i] + k) - A.begin() - i);
    }
    cout << result;
}
