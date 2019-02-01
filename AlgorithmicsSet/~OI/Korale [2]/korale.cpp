#include <bits/stdc++.h>

using namespace std;

template<typename T, T Base, typename ModuloOperation>
struct rolling_hash
{
    ModuloOperation M;
    vector<T> H, P;
    size_t n;
    T X(T a, T b) const
    {
        if(M.divisor < (1LLU << (numeric_limits<T>::digits/2)))
            return M(a * b);
        else
        {
            uint64_t q = (long double)a * b / M.divisor;
            int64_t r = (a*b - q*M.divisor) % M.divisor;
            return r < 0 ? r + M.divisor : r;
            //return x>y ? M(x-y) : (M(y-x) == 0 ? 0 : M.divisor - M(y-x));
        }
    }
    template<typename Iterator>
    rolling_hash(Iterator first, Iterator last, T fix = 0)
    {
        n = distance(first, last);
        H.resize(n+1); P.resize(n+1);
        H[0] = 0; P[0] = 1;
        for(size_t i = 0; i < n; i++, first++)
        {
            H[i+1] = M(X(H[i], Base) + (T(*first)+T(fix)));
            P[i+1] = M(X(P[i], Base));
        }
    }
    T operator() (size_t i, size_t j) const
        { return M(M.divisor + H[j+1] - X(H[i], P[j-i+1])); }
    bool equals(size_t a, size_t b, size_t c, size_t d) const
        { return (*this)(a, b) == (*this)(c, d); }
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
    rolling_hash<uint64_t, 200003, mersenne_modulus<uint64_t, 31>> H(A.begin(), A.end(), 1);
    auto rev = [&](size_t i) {
        return 2*n - i - 1;
    };
    vector<uint32_t> R; uint32_t r = 0;
    for(uint32_t k = 1; k <= n; k++)
    {
        unordered_set<uint64_t> S;
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
