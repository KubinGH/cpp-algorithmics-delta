#include <bits/stdc++.h>

using namespace std;

const size_t MAX_N = 10, MAX_K = 333;
const uint64_t VMOD = 169831;

template<typename T>
constexpr T log2floor(T n)
    { return (numeric_limits<T>::digits-1) - __builtin_clz(n); }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static uint64_t V[MAX_K];
    uint64_t p = 1, mn = 256*n, ln = log2floor(n);
    for(uint32_t i = 0; i < MAX_K; i++)
    {
        V[i] = (p + mn) % VMOD;
        p *= 2; p %= VMOD;
    }
    vector<pair<uint32_t, uint32_t>> G;
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        cin >> u >> v;
        G.emplace_back(u, v);
    }
    static uint32_t K[MAX_N];
    uint64_t r = 0;
    while(true)
    {
        uint64_t c = 0;
        for(uint32_t i = 0; i < n; i++)
            c += V[K[i]];
        bool ok = true;
        for(pair<uint32_t, uint32_t> e : G)
        {
            uint32_t u, v;
            tie(u, v) = e;
            uint32_t k = K[u], d = K[v];
            uint32_t a = (k+333-4*ln) + 128 - k%3, b = (k+333+4*ln) + 128 + k%9;
            a %= 333; b %= 333;
            if(a > b) b += 333, d += 333;
            if(not (a <= d and d <= b))
            {
                ok = false;
                break;
            }
        }
        if(ok)
        {
            r = max(r, c);
            if(r == c)
            {
                cerr << K[0] << " " << K[1] << " " << K[2] << " " << K[3] << " " << c << endl;
                cerr << V[K[0]] << " " << V[K[1]] << " " << V[K[2]] << " " << V[K[3]] << endl;
            }
        }
        K[0]++;
        bool f = false;
        for(uint32_t i = 0; i < n; i++)
        {
            if(K[i] >= MAX_K and i == n - 1)
            {
                f = true; break;
            }
            if(K[i] >= MAX_K)
                K[i+1] += K[i] / MAX_K, K[i] %= MAX_K;
        }
        if(f) break;
    }
    cout << r;
}
