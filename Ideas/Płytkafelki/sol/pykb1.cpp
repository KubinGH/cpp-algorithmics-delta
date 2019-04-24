#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<uint32_t> A(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    using res_t = tuple<uint32_t, uint32_t, uint32_t>;
    res_t result {-1u, -1u, -1u};
    for(uint32_t i = 0; i < n; i++)
        for(uint32_t j = i+1; j < n; j++)
            result = min(result, res_t{-__gcd(A[i], A[j]), i, j});
    cout << -get<0>(result) << "\n" << get<1>(result)+1 << " " << get<2>(result)+1;
}
