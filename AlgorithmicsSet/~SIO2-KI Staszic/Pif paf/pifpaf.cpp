#include <bits/stdc++.h>

using namespace std;

template<typename T, T Base, typename ModuloOperation>
struct rolling_hash
{
    ModuloOperation M;
    vector<T> H, P;
    size_t n;
    template<typename Iterator>
    rolling_hash(Iterator first, Iterator last, T fix = 0)
    {
        n = distance(first, last);
        H.resize(n+1); P.resize(n+1);
        H[0] = 0; P[0] = 1;
        for(size_t i = 0; i < n; i++, first++)
        {
            H[i+1] = M(H[i]*Base + (T(*first)+T(fix)));
            P[i+1] = M(P[i]*Base);
        }
    }
    T operator() (size_t i, size_t j) const
        { return M(M.divisor*M.divisor + H[j+1] - H[i]*P[j-i+1]); }
    bool equals(size_t a, size_t b, size_t c, size_t d) const
        { return (*this)(a, b) == (*this)(c, d); }
};

template<typename T, uint32_t K>
struct mersenne_modulus
{
    static constexpr T P = (T(1) << K) - 1, divisor = P;
    T operator() (T x) const
    {
        x = (x >> K) + (x & P);
        x = (x >> K) + (x & P);
        return x == P ? 0 : x;
    }
};

struct PifPafGenerator
{
    uint32_t next = 0, curr = 0, left = -1u;
    bool yield()
    {
        if(next == 0) { next++; return 0; }
        if(left == -1u)
            left = (31 - __builtin_clz(curr = next++));
        bool b = (curr&(1u<<left))>>left; left--;
        return b;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n; string S;
    cin >> n >> S;
    rolling_hash<uint64_t, 31, mersenne_modulus<uint64_t, 31>>
        H(S.begin(), S.end(), -('a' - 1));
    vector<bool> PifPaf(n); PifPafGenerator gen;
    for(uint32_t i = 0; i < n; i++)
        PifPaf[i] = gen.yield();
    for(uint32_t d = 1; d*2 <= n; d++)
    {
        bool ok = true;
        for(uint32_t i = 2*d, ib = 2; i < n and ok; i += d, ib++)
        {
            bool b = PifPaf[ib];
            uint32_t over = i+d > n ? i + d - n : 0;
            if(H(b*d, b*d+d-(over+1)) != H(i, i+d-(over+1)))
                ok = false;
        }
        if(ok)
        {
            cout << (n+d-1)/d;
            return 0;
        }
    }
    cout << 2;
}
