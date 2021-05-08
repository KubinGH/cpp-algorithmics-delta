#include <bits/stdc++.h>

using namespace std;

constexpr uint64_t mod = 1e9 + 7;

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

    size_t k;
    cin >> k;

    vector<pair<uint64_t, size_t>> G(k);
    for(auto& [x, l] : G)
    {
        string s;
        cin >> s;
        l = s.size();
        x = polynomial_hash::get(s.begin(), s.end());
    }

    polynomial_hash H(S.begin(), S.end());
    vector<uint64_t> W(S.size() + 1); W[0] = 1;
    for(size_t i = 1; i <= S.size(); i++)
        for(auto [x, l] : G)
            if(i >= l and H(i-l, i) == x)
                W[i] += W[i-l], W[i] %= mod;

    cout << W.back() << endl;
}
