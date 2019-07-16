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

    uint32_t m = *max_element(A.begin(), A.end());
    using res_t = tuple<uint32_t, uint32_t, uint32_t>;
    res_t result {-1u, -1u, -1u};

    if(n < 1000)
    {
        for(uint32_t i = 0; i < n; i++)
            for(uint32_t j = i+1; j < n; j++)
                result = min(result, res_t{-__gcd(A[i], A[j]), i, j});
    }
    else
    {
        vector<uint32_t> E(m+1, -1u);
        for(uint32_t i = 0; i < n; i++)
        {
            E[A[i]] = min(E[A[i]], i);
            for(uint32_t d = 1; d*d <= n; d++)
            {
                if(E[d])
                    result = min(result, res_t{-d, E[d], i});
                if(E[n/d])
                    result = min(result, res_t{-n/d, E[n/d], i});
            }
        }
    }
    cout << -get<0>(result) << "\n" << get<1>(result)+1 << " " << get<2>(result)+1;
}
