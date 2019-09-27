#include <bits/stdc++.h>

using namespace std;

int main()
{
    uint64_t n; uint m;
    cin >> n >> m;

    const uint K = 4;
    vector<uint64_t> F(m*K);
    F[0] = 1; F[1] = 0;
    for(uint64_t i = 2; i < m*K; i++)
        F[i] = ((i - 1) * (F[i-1] + F[i-2])) % m;

    auto f = F[n % (m*K)];

    cout << (f*f)%m << endl;
}
