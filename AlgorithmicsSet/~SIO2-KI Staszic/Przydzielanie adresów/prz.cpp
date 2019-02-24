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

template<typename T>
struct identity
{
    static constexpr T divisor = 0;
    T operator() (T x) const { return x; }
};
template<typename T, uint32_t K>
struct mersenne_modulus
{
    static constexpr T P = (T(1) << K) - 1, divisor = P;
    T operator() (T x) const
    {
        for(uint32_t i = K; i < numeric_limits<T>::digits; i += K-1)
            x = (x >> K) + (x & P);
        return x == P ? 0 : x;
    }
};

template<typename First, typename Second>
struct rolling_hash_pair
{
    First H; Second G;
    rolling_hash_pair(First h, Second g) : H(move(h)), G(move(g)) {}
    using T1 = typename result_of< First(size_t, size_t)>::type;
    using T2 = typename result_of<Second(size_t, size_t)>::type;
    pair<T1, T2> operator() (size_t i, size_t j) const
        { return {H(i, j), G(i, j)}; }
    bool equals(size_t a, size_t b, size_t c, size_t d)
        { return H.equals(a, b, c, d) and G.equals(a, b, c, d); }
};

using rhash = rolling_hash_pair<
    rolling_hash<uint64_t, 331, mersenne_modulus<uint64_t, 31>>,
    rolling_hash<uint64_t, 331, identity<uint64_t>>
>;
using hash_cell = result_of<rhash(size_t, size_t)>::type;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string S;
    cin >> S;
    const uint32_t n = S.size();
    uint32_t q;
    cin >> q;
    vector<hash_cell> E; E.reserve(n);
    rhash H({S.begin(), S.end(), -CHAR_MIN}, {S.begin(), S.end(), -CHAR_MIN});
    while(q --> 0)
    {
        uint32_t m;
        cin >> m;
        vector<string> T(m);
        for(uint32_t i = 0; i < m; i++)
            cin >> T[i];
        uint32_t k = T[0].size();
        E.clear();
        for(uint32_t i = 0; i+k <= n; i++)
            E.push_back(H(i, i+k-1));
        sort(E.begin(), E.end());
        for(const auto& t : T)
        {
            rhash h({t.begin(), t.end(), -CHAR_MIN}, {t.begin(), t.end(), -CHAR_MIN});
            if(binary_search(E.begin(), E.end(), h(0, k-1)))
                cout << "OK\n";
            else
                cout << "NIE\n";
        }
    }
}
