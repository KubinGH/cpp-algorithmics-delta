#include <bits/stdc++.h>

using namespace std;

static constexpr uint64_t Exp = 31, MerPrime = (1u << Exp) - 1, Base = 31, Base2 = 33;
uint M(uint64_t x)
{
    x = (x >> Exp) + (x & MerPrime);
    x = (x >> Exp) + (x & MerPrime);
    return x != MerPrime ? x : 0;
}

struct rolling_hash
{
    size_t n;
    vector<uint> P, Q, H, G;

    template<typename It>
    rolling_hash(It first, It last) : n(distance(first, last)), P(n+1), Q(n+1), H(n+1), G(n+1)
    {
        P[0] = Q[0] = 1;
        for(size_t i = 0; i < n; i++, ++first)
        {
            P[i+1] = M(Base*P[i]);
            Q[i+1] = Base2*Q[i];
            uint x = *first - 'a' + 1;
            H[i+1] = M(Base*H[i] + x);
            G[i+1] = Base2*G[i] + x;
        }
    }

    // [i, j)
    pair<uint, uint> operator() (size_t i, size_t j)
    {
        return {
            M(MerPrime*MerPrime + H[j] - (uint64_t)H[i]*P[j-i]),
            G[j] - G[i]*Q[j-i]
        };
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    string S;
    cin >> n >> S;

    rolling_hash H(S.begin(), S.end());

    vector<pair<pair<uint, uint>, size_t>> data;
    data.reserve(n);

    size_t lo = 1, hi = n;
    while(lo < hi)
    {
        size_t mid = (lo + hi) / 2;

        data.clear();
        for(size_t i = 0; i+mid <= n; i++)
            data.emplace_back(H(i, i+mid), i);
        sort(data.begin(), data.end());

        bool found = false;
        for(size_t i = 0, j = 0; i < data.size(); i = j+1, j = i)
        {
            while(j+1 < data.size() and data[i].first == data[j+1].first)
                j++;
            if(data[j].second - data[i].second >= mid)
                found = true;
        }

        if(not found)
            hi = mid;
        else
            lo = mid+1;
    }
    cout << lo - 1 << endl;
}
