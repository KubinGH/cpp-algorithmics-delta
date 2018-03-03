#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;

uint32_t pmul(uint32_t a, uint32_t b, uint32_t mod)
{
    if(a > b) swap(a, b);
    uint32_t p = (a * (b / 4)) % mod;
    return ((4 * p) % mod + ((b % 4) * a) % mod) % mod;
}

uint32_t fast_pow(uint32_t b, uint32_t n, uint32_t mod)
{
    uint32_t r = 1;
    while(n)
    {
        if(n % 2)
        {
            r = pmul(r, b, mod);
        }
        b = pmul(b, b, mod);
        n /= 2;
    }
    return r;
}

array<uint32_t, MAX> CACHE;
uint32_t next(uint32_t y, uint32_t p, uint32_t mod)
{
    if(CACHE[y] != -1u)
        return CACHE[y];
    uint32_t x = 0, by = y;
    while(y)
    {
        uint32_t t = fast_pow(y % 10, p, mod);
        x += t;
        x %= mod;
        y /= 10;
    }
    CACHE[by] = x;
    return x;
}

template<typename T, size_t SIZE>
struct fstack
{
    array<T, SIZE> A;
    uint32_t i = 0;
    void clear()
    {
        i = 0;
    }
    T& top()
    {
        return A[i-1];
    }
    void pop()
    {
        i--;
    }
    void push(T o)
    {
        A[i] = o;
        i++;
    }
    bool empty()
    {
        return i == 0;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    CACHE.fill(-1u);
    uint32_t n, p, m;
    cin >> n >> p >> m;
    static array<uint32_t, MAX> V;
    V.fill(-1u);
    static array<int32_t, MAX> T;
    T.fill(-1);
    for(uint32_t k = 1; k <= n; k++)
    {
        uint32_t x = k, b = 0;
        int32_t t = 0;
        static fstack<uint32_t, MAX> S; S.clear();
        while(T[x] == -1 and V[x] == -1u)
        {
            T[x] = t++;
            S.push(x);
            x = next(x, p, m);
        }
        if(T[x] != -1)
        {
            b = x;
            uint32_t v = t - T[b];
            bool f = false;
            while(not S.empty())
            {
                V[S.top()] = v;
                if(S.top() == b) f = true;
                if(f) v++;
                T[S.top()] = -1;
                S.pop();
            }
            x = k; t = 0;
            T[b] = -1;
        }
        while(not S.empty())
            T[S.top()] = -1, S.pop();
        cout << t + V[x] << " ";
    }
}
