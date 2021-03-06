#include <iostream>
#include <vector>
#include <cstring>
#define RANDTEST
#ifdef XHOVA
#include <bits/stdc++.h>
#else
#define cerr if(0) cerr
#endif

using namespace std;

const size_t MAX = 1 << 19;

template<typename T, T MOD, T BASE, size_t N>
struct rolling_hash
{
    T H[N];
    T base_pow[N];
    size_t n;
    template<typename Iterator>
    rolling_hash(Iterator first, Iterator last, T fix = 0)
    {
        n = distance(first, last);
        auto it = first;
        for(size_t i = 0; i < n; i++, it++)
        {
            H[i] = T('z' - *it + 1);
            if(i)
                H[i] += BASE * H[i-1], base_pow[i] = BASE * base_pow[i-1];
            else
                base_pow[i] = 1;
            H[i] %= MOD, base_pow[i] %= MOD;
        }
    }
    const T& operator[] (size_t i) const { return H[i]; }
    T operator() (size_t i, size_t j) const
    {
        if(i == 0)
            return H[j];
        else
            return (2*MOD + H[j] - (H[i-1] * base_pow[j - i + 1])%MOD) % MOD;
    }
};

#ifdef RANDTEST
typedef rolling_hash<uint64_t, uint64_t(1e9+33), 31LLU, 2048> rhash;
#else
typedef rolling_hash<uint64_t, uint64_t(1e9+33), 31LLU, MAX> rhash;
#endif // RANDTEST

uint32_t
diffcount(const char (&S)[MAX], uint32_t x, uint32_t y, uint32_t n)
{
    uint32_t r = 0;
    for(uint32_t i = 0; i < n; i++)
        if(S[x+i] != S[y+i])
            r++;
    return r;
}

uint32_t
diffcount(const char (&S)[MAX], rhash& H,
          uint32_t x, uint32_t y, uint32_t n)
{
    if(H(x, x+n-1) == H(y, y+n-1))
        return 0;
    uint32_t lo = 0, hi = n;
    while(lo < hi)
    {
        uint32_t mid = (lo + hi) / 2;
        if(H(x, x+mid) != H(y, y+mid))
            hi = mid;
        else
            lo = mid + 1;
    }
    if(lo == n)
        return 0;
    else if(lo == n - 1 or H(x+lo+1, x+n-1) == H(y+lo+1, y+n-1))
        return 1;
    else
        return 2;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    static char S[MAX];
#ifdef RANDTEST
    srand(time(0));
for(uint32_t _t = 0; _t < (1 << 12); _t++) {
    for(uint32_t i = 0; i < 12; i++)
        S[i] = ((_t & (1u << i)) != 0)+'a';
    cout << endl << S << endl;
#else
    cin >> S;
#endif
    uint32_t n = strlen(S);
#ifdef RANDTEST
    rhash H(S, S + n, -uint64_t('a' - 1));
#else
    static rhash H(S, S + n);
#endif
    vector<uint32_t> R;
    for(uint32_t d = 1; d < n; d++)
    {
        uint32_t q[2];
        q[0] = 1; q[1] = 0;
        uint32_t p = 0;
        bool ok = true;
        //cerr << d << ": " << endl;
        for(uint32_t i = d; i < n and ok; i += d)
        {
            uint32_t w = i+d <= n ? d : n-i;
            uint32_t c[2];
            c[0] = diffcount(S, H, 0, i, w);
            c[1] = q[1] ? diffcount(S, H, p, i, w) : 0;
            //cerr << i << ".." << i+w << ": " << c[0] << " " << c[1] << endl;
            if(c[0] == 0 and c[1] == 0 and q[0] < q[1])
                q[1]++;
            else if(c[0] == 0)
            {
                q[0]++;
            }
            else if(c[0] == 1)
            {
                if(q[1] == 0)
                {
                    q[1]++;
                    p = i;
                }
                else if(c[1] == 0)
                {
                    q[1]++;
                }
                else
                {
                    ok = false;
                }
            }
            else
            {
                ok = false;
            }
        }
        //cerr << q[0] << " " << q[1] << " (" << ok << ")" << endl << endl;
        if(ok and (q[0] <= 1 or q[1] <= 1))
            R.push_back(d);
    }
    cout << R.size() << "\n";
    for(uint32_t x : R)
        cout << x << " ";

#ifdef XHOVA
    cout << endl;
    for(uint32_t d = 1; d < n; d++)
    {
        bool any = false;
        static char Q[MAX];
        for(char ch = 'a'; ch <= 'z' and not any; ch++)
          for(uint32_t ci = 0; ci < n and not any; ci++)
        {
            copy(S, S + n, Q);
            Q[ci] = ch;
            bool ok = true;
            for(uint32_t i = d; i < n and ok; i += d)
            {
                uint32_t w = i+d <= n ? d : n-i;
                if(diffcount(Q, 0, i, w) > 0)
                    ok = false;
            }
            if(ok)
                any = true;
        }
        if(any)
        {
            cout << d << " ";
            cout.flush();
            assert(binary_search(R.begin(), R.end(), d));
        }
        else
            assert(not binary_search(R.begin(), R.end(), d));
    }
#ifdef RANDTEST
}
#endif
#endif
}
/*

*/
