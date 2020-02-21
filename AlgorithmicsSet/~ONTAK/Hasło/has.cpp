#include <bits/stdc++.h>

using namespace std;

const uint K = 31, Mod = (1u << K) - 1;
uint M(uint64_t x)
{
    x++;
    x = (x & Mod) + (x >> K);
    x = (x & Mod) + (x >> K);
    return x - 1;
}


int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    string S;
    cin >> S;

    vector<uint> H(n+1), P(n+1);
    P[0] = 1;
    for(size_t i = 0; i < n; i++)
    {
        H[i+1] = M((uint64_t)H[i]*K + uint(S[i]-'a'));
        P[i+1] = M((uint64_t)P[i]*K);
    }
    auto h = [&](size_t i, size_t j) {
        return M((uint64_t)Mod*Mod + H[j] - (uint64_t)H[i]*P[j-i]);
    };

    auto h_mismatch = [&](size_t a, size_t b, size_t k) {
        size_t lo = 1, hi = k + 1;
        while(lo < hi)
        {
            auto mid = (lo + hi) / 2;
            if(h(a, a + mid) != h(b, b + mid))
                hi = mid;
            else
                lo = mid + 1;
        }
        return lo - 1;
    };
    auto one_mismatch = [&](size_t a, size_t b, size_t k) {
        auto l = h_mismatch(a, b, k);
        return l < k and h(a+l+1, a+k) == h(b+l+1, b+k);
    };

    bool done = false;
    for(size_t k = n/2+1; not done and k --> 1; )
    {
        if(one_mismatch(0, n-k, k))
        {
            cout << n-k << endl;
            done = true;
        }
    }
    if(not done)
        cout << "-1" << endl;
}
