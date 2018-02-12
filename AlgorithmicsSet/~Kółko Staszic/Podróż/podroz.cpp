#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 10000000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    uint32_t q;
    cin >> q;
    for(uint32_t i = 0; i < q; i++)
    {
        uint32_t a, b;
        cin >> a >> b;
        cout << lower_bound(A.begin(), A.begin() + n, b)
              - lower_bound(A.begin(), A.begin() + n, a) << '\n';
    }
}
