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

    string S, T;
    cin >> S >> T;

    polynomial_hash H(S.begin(), S.end());
    auto h = polynomial_hash::get(T.begin(), T.end());

    size_t r = 0;
    for(size_t i = 0; i+T.size() <= S.size(); i++)
        r += H(i, i+T.size()) == h;

    cout << r << endl;
}
