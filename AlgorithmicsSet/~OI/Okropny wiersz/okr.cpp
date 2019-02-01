#include <bits/stdc++.h>

using namespace std;

constexpr uint64_t Base = 331;
uint64_t M(uint64_t x)
{
    x = (x >> 31) + (x & ((1llu<<31)-1));
    x = (x >> 31) + (x & ((1llu<<31)-1));
    return x;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;

    vector<uint64_t> B(n+1);
    B[0] = 1;
    for(uint32_t i = 1; i <= n; i++)
        B[i] = M(B[i-1] * Base);

    string S;
    cin >> S;
    vector<uint64_t> H(n);
    for(uint32_t i = 0; i < n; i++)
    {
        if(i) H[i] = H[i-1]*Base;
        H[i] += S[i] - 'a' + 1;
        H[i] = M(H[i]);
    }

    const uint64_t D = (1llu<<31)-1, D2 = D*D;
    auto equals = [&](uint32_t a, uint32_t b, uint32_t c, uint32_t d) {
        return (a ? M(D2 + H[b] - H[a-1]*B[b-a+1]) : H[b]) ==
               (c ? M(D2 + H[d] - H[c-1]*B[d-c+1]) : H[d]);
    };

    uint32_t q;
    cin >> q;

    vector<bool> mark(n+1);
    vector<pair<uint32_t, uint32_t>> queries(q);
    for(uint32_t i = 0; i < q; i++)
    {
        cin >> queries[i].first >> queries[i].second;
        mark[queries[i].second - queries[i].first + 1] = true;
    }

    vector<vector<uint32_t>> factors(n+1);
    for(uint32_t i = 1; i <= n; i++)
        for(uint32_t x = i; x <= n; x += i)
            if(mark[x]) factors[x].push_back(i);

    for(uint32_t i = 0; i < q; i++)
    {
        uint32_t L, R;
        tie(L, R) = queries[i]; L--; R--;
        uint32_t r = R-L+1;
        for(uint32_t k : factors[R-L+1])
            if(equals(L, R-k, L+k, R))
                { r = k; break; }
        cout << r << "\n";
    }
}
