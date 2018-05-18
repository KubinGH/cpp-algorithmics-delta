#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e6;

template<typename T, T MOD, T BASE, size_t N>
struct basehash
{
    T H[N];
    T base_pow[N];
    size_t n;
    basehash() {}
    template<typename Iterator>
    void reinit(Iterator begin, Iterator end, T fix = 0)
    {
        n = distance(begin, end);
        Iterator it = begin;
        for(uint32_t i = 0; i < n; i++)
        {
            if(i > 0)
                H[i] = H[i-1] * BASE, H[i] %= MOD;
            H[i] += T(*it) + fix;
            H[i] %= MOD;

            if(i > 0)
                base_pow[i] = (base_pow[i-1] * BASE) % MOD;
            else
                base_pow[i] = 1;
            it++;
        }
    }
    const T& operator[] (size_t i) const { return H[i]; }
    T operator() (size_t i, size_t j) const
    {
        if(i == 0)
            return H[j];
        else
            return (2*MOD + H[j] - ((H[i-1]*base_pow[j - i + 1]) % MOD)) % MOD;
    }
};

basehash<uint64_t, (uint64_t)(1e9+33), 29, MAX> H, RH;
bool pal(uint32_t q, uint32_t p, uint32_t n)
    { return H(q, p) == RH((n-1)-p, (n-1)-q); }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    static char IT[MAX+1];
    cin >> n >> IT;
    static uint32_t T[MAX];
    for(uint32_t i = 0; i < n; i++)
        T[i] = IT[i] - 'a' + 1;
    static uint32_t RT[MAX];
    copy(T, T + n, RT);
    reverse(RT, RT + n);
    uint32_t r = 0;
    uint32_t a = 0, b = n-1;
    while(a < b and T[a] == T[b])
        r += 2, a++, b--;
    if(a == b)
        { cout << n; return 0; }
    else if(a > b)
        { cout << n - 1; return 0; }
    uint32_t d = b - a + 1;
    H.reinit(T, T + n), RH.reinit(RT, RT + n);
    uint32_t lo = 0, hi = d/2+1, v = 0;
    while(lo < hi)
    {
        uint32_t ix = (lo + hi) / 2, x = 2*ix;
        bool found = x == 0;
        for(uint32_t i = a; i < b - x + 1 and not found; i++)
            if(pal(i, i+x, n))
                found = true;
        if(found)
            lo = ix + 1, v = max(v, x);
        else
            hi = ix;
    }
    r += v+1;
    cout << r;
}
