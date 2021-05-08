#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int64_t n; size_t k;
    cin >> n >> k;

    vector<int64_t> P(k);
    for(auto& p : P)
        cin >> p;

    int64_t result = n;
    for(size_t mask = 0; mask < (1u << k); mask++)
    {
        int64_t prod = 1;
        for(size_t i = 0; i < k and prod; i++)
            if(mask >> i & 1)
                prod = P[i] > n / prod ? 0 : prod * P[i];
        if(prod)
            result += (__builtin_parity(mask) ? 1 : -1) * (n / prod);
    }

    cout << result << endl;
}
