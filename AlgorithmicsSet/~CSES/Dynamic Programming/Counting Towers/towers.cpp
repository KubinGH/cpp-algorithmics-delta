#include <bits/stdc++.h>

using namespace std;

const uint64_t mod = 1e9 + 7;

int main()
{
    size_t t;
    cin >> t;
    vector<size_t> N(t);
    for(auto& n : N)
        cin >> n;

    auto m = *max_element(N.begin(), N.end());

    vector<uint64_t> R(m+1); R[0] = 1;
    uint64_t s = 1, z = 0, p = 1;
    for(size_t n = 1; n <= m; n++)
    {
        R[n] += s + z + p; R[n] %= mod;
        z = (4*z + s) % mod;
        s = (s + R[n]) % mod;
        p = 4*p % mod;
    }

    for(auto n : N)
        cout << R[n] << '\n';
}
