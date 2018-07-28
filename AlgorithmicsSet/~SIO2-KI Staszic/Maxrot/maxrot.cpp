#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 21;

template<typename T, size_t N, T BASE, T MOD = 0>
struct rolling_hash
{
    size_t n;
    T A[N], H[N], B[N];
    template<typename Iterator>
    void init(Iterator begin, Iterator end, T fix = 0)
    {
        n = distance(begin, end);
        Iterator it = begin;
        for(size_t i = 0; i < n; i++, it++)
        {
            if(i == 0)
                B[i] = 1;
            else
                H[i] = H[i-1]*BASE, B[i] = B[i-1]*BASE;
            H[i] += (A[i] = (T(*it) + fix));
            if(MOD) { H[i] %= MOD; B[i] %= MOD; }
        }
    }
    template<typename Iterator>
    rolling_hash(Iterator begin, Iterator end, T fix = 0)
        { init(begin, end, fix); }
    inline T operator() (size_t i, size_t j) const
    {
        if(i == 0)
            return H[j];
        else
        {
            if(MOD)
                return (MOD + H[j] - (H[i-1] * B[j-i+1]) % MOD) % MOD;
            else
                return H[j] - H[i-1]*B[j-i+1];
        }
    }
};
typedef rolling_hash<uint32_t, MAX, 29> rhash;

int main()
{
  ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  uint32_t t;
  cin >> t;
  while(t --> 0)
  {
    static char S[MAX];
    uint32_t n;
    cin >> n >> S;
    copy(S, S + n, S + n); S[2*n] = 0;
    static rhash H(S, S);
    H.init(S, S + 2*n, -('a' - 1));
    uint32_t r = 0;
    for(uint32_t p = 1; p < n; p++)
    {
        uint32_t lo = 0, hi = n;
        while(lo < hi)
        {
            uint32_t m = (lo + hi) / 2;
            if(m == 0 or H(p, p+m-1) == H(r, r+m-1))
                lo = m + 1;
            else
                hi = m;
        }
        if(lo < n and S[p+lo-1] > S[r+lo-1])
            r = p;
    }
    for(uint32_t i = r; i < r + n; i++)
        cout << S[i];
    cout << "\n";
  }
}
