#include <bits/stdc++.h>

using namespace std;

const uint64_t K = 31, P = (1ul << K) - 1;
uint mmod(uint64_t x)
{
    x++;
    x = (x >> K) + (x & P);
    x = (x >> K) + (x & P);
    return x - 1;
}

const uint64_t B = 257;
vector<uint> bpow = {1};

struct rolling_hash
{
    vector<uint> H;
    template<typename It>
    rolling_hash(It first, It last)
    {
        H.push_back(0);
        while(first != last)
            H.push_back(mmod(B*H.back() + *first++));
        while(bpow.size() < H.size())
            bpow.push_back(mmod(B*bpow.back()));
    }

    uint operator() (size_t l, size_t r) const
    {
        return mmod(P*P + H[r] - (uint64_t)H[l]*bpow[r-l]);
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t t;
    cin >> t;

    while(t --> 0)
    {
        string S;
        cin >> S;

        const size_t n = S.size();
        rolling_hash H(S.begin(), S.end());
        vector<size_t> suff(n);
        iota(suff.begin(), suff.end(), 0);
        sort(suff.begin(), suff.end(), [&](size_t i, size_t j) {
            size_t lo = 0, hi = n - max(i, j);
            while(lo < hi)
            {
                auto mid = (lo + hi) / 2;
                if(H(i, i + mid) != H(j, j + mid))
                    hi = mid;
                else
                    lo = mid + 1;
            }
            return S[i+lo] < S[j+lo];
        });

        vector<int> R(n/2 + 1, 1);
        R.back() = n % 2;
        vector<bool> done(n/2 + 1);
        function<int(size_t)> get = [&](size_t i) {
            if(done[i])
                return R[i];
            done[i] = true;
            for(size_t j = i+1; j <= n/2; j++)
                if(H(i, j) == H(n-j, n-i))
                    return R[i] = get(j) + 2;
            return R[i];
        };
        cout << get(0) << endl;
    }
}
