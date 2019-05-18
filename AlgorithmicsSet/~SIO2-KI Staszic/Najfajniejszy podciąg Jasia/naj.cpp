#include <bits/stdc++.h>

using namespace std;

int main()
{
    size_t n;
    cin >> n;

    vector<uint32_t> A(n), B(n);
    for(size_t i = 0; i < n; i++)
        cin >> A[i];
    for(size_t i = 0; i < n; i++)
        cin >> B[i];

    vector<uint32_t> last(n + 1), curr(n + 1);
    for(size_t i = 1; i <= n; i++)
    {
        curr.swap(last);
        for(size_t j = 1; j <= n; j++)
            curr[j] = A[i-1]==B[j-1] ? last[j-1] + A[i-1] : max(last[j], curr[j-1]);
    }
    cout << curr[n];
}
