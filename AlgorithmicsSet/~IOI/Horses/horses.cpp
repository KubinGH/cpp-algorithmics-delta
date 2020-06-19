#include <bits/stdc++.h>

using namespace std;

size_t n;
uint X[1 << 19], Y[1 << 19];
uint64_t product = 1;
set<size_t> idx;

const uint MOD = 1e9 + 7;
uint power(uint a, uint b)
{
    uint r = 1;
    while(b)
    {
        if(b % 2) r = (uint64_t) r * a % MOD;
        a = (uint64_t) a * a % MOD;
        b /= 2;
    }
    return r;
}
uint inverse(uint x) { return power(x, MOD - 2); }

struct segment_tree
{
    const size_t w = 1 << 19;
    uint values[1 << 20];
    void set(size_t pos, uint val)
    {
        values[pos += w] = val;
        while(pos /= 2)
            values[pos] = max(values[2*pos], values[2*pos+1]);
    }

    uint get(size_t l, size_t r)
    {
        uint result = 0;
        for(l += w, r += w; l < r; l /= 2, r /= 2)
        {
            if(l % 2) result = max(result, values[l++]);
            if(r % 2) result = max(result, values[--r]);
        }
        return result;
    }
} treeY;

uint maxY(size_t l, size_t r)
{
    return treeY.get(l, r);
}

uint compute()
{
    uint64_t yj = Y[n-1], li = 1, lj = 1;
    for(auto it = --idx.end(); *it > 0 and li < UINT_MAX; )
    {
        auto i = *it, i1 = *prev(it);
        auto yi = maxY(i1, i);
        if(yj * li < yi * lj)
            yj = yi, lj = li;
        li *= X[i1];
        it = prev(it);
    }

    return product * inverse(lj) % MOD * yj % MOD;
}

int init(int _n, int x[], int y[])
{
    n = _n;
    copy(x, x + n, X);
    copy(y, y + n, Y);
    for(size_t i = 0; i < n; i++)
    {
        product = product * X[i] % MOD;
        if(X[i] > 1) idx.insert(i);
        treeY.set(i, Y[i]);
    }
    idx.insert(0); idx.insert(n);
    X[n] = 1;
    return compute();
}

int updateX(int pos, int val)
{
    product = product * inverse(X[pos]) % MOD * val % MOD;
    if(pos and X[pos] > 1) idx.erase(pos);
    if(val > 1)            idx.insert(pos);
    X[pos] = val;
    return compute();
}

int updateY(int pos, int val)
{
    Y[pos] = val;
    treeY.set(pos, val);
    return compute();
}
