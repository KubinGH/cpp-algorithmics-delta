#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<uint64_t> A(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    sort(A.begin(), A.end());
    uint32_t q;
    cin >> q;
    for(uint32_t i = 0; i < q; i++)
    {
        uint64_t x;
        cin >> x;
        auto range = equal_range(A.begin(), A.end(), x);
        cout << range.second - range.first << "\n";
    }
}
