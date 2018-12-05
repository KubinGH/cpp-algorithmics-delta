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
            H[i+1] = M(M(H[i]*Base) + M(T(*first)+fix));
            P[i+1] = M(P[i]*Base);
        }
    }
    T operator() (size_t i, size_t j) const
        { return M(M.dividend + H[j+1] - M(H[i] * P[j-i+1])); }
    bool equals(size_t a, size_t b, size_t c, size_t d) const
        { return (*this)(a, b) == (*this)(c, d); }
};

template<typename T, uint32_t K>
struct mersenne_modulus
{
    const T P = (T(1) << K) - 1, dividend = P;
    T operator() (T x) const
    {
        x = (x >> K) + (x & P);
        x = (x >> K) + (x & P);
        return x;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string S, T;
    cin >> S >> T;
    string P = S + '#' + T; uint32_t fix = -('a' - 1), tfix = S.size()+1;
    rolling_hash<uint64_t, 31, mersenne_modulus<uint64_t, 31>> H(P.begin(), P.end(), fix);
    uint32_t r = 0;
    for(uint32_t i = 0; i+S.size() <= T.size(); i++)
    {
        uint32_t lo = 0, hi = S.size();
        while(lo < hi)
        {
            uint32_t mid = (lo + hi) / 2;
            if(not H.equals(0, mid, tfix + i, tfix + i+mid))
                hi = mid;
            else
                lo = mid+1;
        }

        if(lo >= S.size()-1 or H.equals(lo+1, S.size()-1,
                                        tfix + i+lo+1, tfix + i+S.size()-1))
            r++;
    }
    cout << r;
}
