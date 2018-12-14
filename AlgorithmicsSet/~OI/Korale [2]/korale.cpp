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
        x = (x >> K) + (x & P);
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

typedef rolling_hash_pair<
    rolling_hash<uint64_t, 200003, mersenne_modulus<uint64_t, 31>>,
    rolling_hash<uint64_t, 200009, identity<uint64_t>>
> this_hash;

struct hash_2size
{
    size_t operator() (const pair<size_t, size_t>& p) const
    {
        return 313*31*17*13*11*
               ((uint64_t(p.first<<16) * uint64_t(p.second)) % ((1llu<<31)-1));
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<uint32_t> A(2*n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    for(uint32_t i = n; i --> 0; )
        A[2*n-i-1] = A[i];
    this_hash H({A.begin(), A.end(), 1}, {A.begin(), A.end(), 1});
    auto rev = [&](size_t i) {
        return 2*n - i - 1;
    };
    vector<uint32_t> R; uint32_t r = 0;
    for(uint32_t k = 1; k <= n; k++)
    {
        unordered_set<pair<size_t, size_t>, hash_2size> S;
        for(uint32_t i = 0; i+k <= n; i += k)
        {
            auto h = H(i, i+k-1); auto g = H(rev(i+k-1), rev(i));
            S.insert(min(h, g));
        }
        if(S.size() > r)
            r = S.size(), R.clear();
        if(S.size() == r)
            R.push_back(k);
    }
    cout << r << " " << R.size() << "\n";
    for(uint32_t k : R)
        cout << k << " ";
}
