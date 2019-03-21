#include <bits/stdc++.h>
#define note(__val) #__val << " = " << (__val)

using namespace std;

template<typename T, T Base, typename ModuloOperation>
struct rolling_hash
{
    struct _identity { T operator() (const T& x) { return x; } };
    static ModuloOperation M;
    vector<T> H, P;
    size_t n;
    template<typename Iterator, typename Fix>
    rolling_hash(Iterator first, Iterator last, Fix F = _identity())
    {
        n = distance(first, last);
        H.resize(n+1); P.resize(n+1);
        H[0] = 0; P[0] = 1;
        for(size_t i = 0; i < n; i++, first++)
        {
            H[i+1] = M(H[i]*Base + F(T(*first)));
            P[i+1] = M(P[i]*Base);
        }
    }
    T operator() (size_t i, size_t j) const
        { return M(M.divisor*M.divisor + H[j+1] - H[i]*P[j-i+1]); }
    bool equals(size_t a, size_t b, size_t c, size_t d) const
        { return (*this)(a, b) == (*this)(c, d); }
};

template<typename T>
struct identity
{
    static constexpr T divisor = 0;
    T operator() (T x) const { return x; }
};

using qhash = rolling_hash<uint32_t, 5, identity<uint32_t>>;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    uint32_t n;
    cin >> n;

    string S;
    cin >> S;

    string Z = S;
    reverse(Z.begin(), Z.end());
    for(auto& c : Z)
        c ^= 1;

    string T = S + Z;

    qhash H(T.begin(), T.end(), [](char c) { return c == '0' ? 2 : 3; });

    uint64_t result = 0;

    auto assymetric = [&](uint32_t i, uint32_t r) {
        return H(i, i+r-1) == H(2*n-1 - (i-1), 2*n-1 - (i-r));
    };

    for(uint32_t i = 1; i < n; i++)
    {
        uint32_t lo = 1, hi = min(i, n-i) + 1;
        while(lo < hi)
        {
            uint32_t mid = (lo + hi) / 2;
            if(not assymetric(i, mid))
                hi = mid;
            else
                lo = mid+1;
        }
        result += lo - 1;
    }

    cout << result;
}
