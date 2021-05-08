#include <bits/stdc++.h>

using namespace std;

__extension__ using uint128_t = unsigned __int128;
constexpr uint64_t K = 61, P = (1ul<<K) - 1, B = 61;

uint64_t M(uint128_t x)
{
    x++;
    x = (x >> K) + (x & P);
    x = (x >> K) + (x & P);
    return x - 1;
}

vector<uint64_t> E = {1};
struct polynomial_hash
{
    vector<uint64_t> H;
    template<typename It>
    polynomial_hash(It first, It last)
    {
        H.push_back(0);
        do {
            H.push_back(M((uint64_t)(*first) + (uint128_t)B*H.back()));
        } while(++first != last);
        while(E.size() <= H.size())
            E.push_back(M((uint128_t)B*E.back()));
    }

    template<typename It>
    static uint64_t get(It first, It last)
    {
        uint64_t h = 0;
        do {
            h = M((uint64_t)(*first) + (uint128_t)B*h);
        } while(++first != last);
        return h;
    }

    uint64_t operator() (size_t l, size_t r) const
    {
        return M((uint128_t)P*P + H[r] - (uint128_t)H[l]*E[r-l]);
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    string S;
    cin >> S;
    const size_t n = S.size();
    S += S;
    polynomial_hash H(S.begin(), S.end());

    auto mismatch = [&](size_t a, size_t b, size_t m) {
        size_t lo = 0, hi = m;
        while(lo < hi)
        {
            auto mid = (lo + hi) / 2;
            if(H(a, a+mid+1) != H(b, b+mid+1))
                hi = mid;
            else
                lo = mid+1;
        }
        return lo;
    };

    auto lex_cmp = [&](size_t a, size_t b) {
        auto k = mismatch(a, b, n);
        return k < n ? S[a+k] < S[b+k] : false;
    };

    vector<size_t> I(n);
    iota(I.begin(), I.end(), 0);
    auto r = *min_element(I.begin(), I.end(), lex_cmp);

    cout << S.substr(r, n) << endl;
}
