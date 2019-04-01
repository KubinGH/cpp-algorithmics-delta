// To nie jest tak, że zadanie jest fajne albo nie fajne. Gdybym miał
// powiedzieć, co cenię w zadankach najbardziej, to powiedziałbym,
// że ludzi, którzy je tworzą. Ludzi, którzy pisali te zadania z 
// własnego serca, którzy zaproponowali mi dobre zadanko, kiedy
// tego potrzebowałem. I właśnie to cenię w życiu najbardziej.
// Zresztą, kto wie, dzisiaj rozwiązuję sobie sesję próbną II etapu,
// a następnego dnia, oddam się na przykład, hm, pracy społecznej, 
// to znaczy, może, hm, będę debugował młodszym kolegom geo.

#include <vector>
#include <cstdint>

using namespace std;

template<typename T>
struct fenwick_tree
{
    static constexpr inline size_t lsb(size_t x) { return x & -x; }
    size_t n;
    vector<T> F;
    T total;
    fenwick_tree(size_t _n) : n(_n), F(n+1), total(0) {}
    fenwick_tree() : fenwick_tree(0) {}
    inline void resize(size_t m) 
    {
        n = m;
        total = 0;
        fill(F.begin(), F.end(), 0);
        F.resize(n+1);
    }
    inline T get_prefix(size_t i) const
    {
        T r = 0;
        while(i)
            r += F[i], i &= i - 1;
        return r;
    }
    inline void delta(size_t i, T v)
    {
        i++;
        total += v;
        while(i <= n)
            F[i] += v, i += lsb(i);
    }
    
    inline T get_suffix(size_t i) const { return total - get_prefix(n - i); }
    inline T get(size_t i, size_t j) const { return get_prefix(j+1) - get_prefix(i); }
    inline void set(size_t i, T v) { delta(i, get_prefix(i) - get_prefix(i+1) + v); }
};

size_t n, length, overprefix;
int64_t overprefix_sum = 0;
fenwick_tree<int64_t> F;

inline void initialize(size_t m)
{
    n = m;
    F.resize(n);
    length = 0; overprefix = 0;
    overprefix_sum = 0;
}

inline void push_back(int64_t v)
{
    F.set(overprefix, v);
    length++; overprefix++;
    if(overprefix == n)
        overprefix = 0, overprefix_sum = 0;
    else
        overprefix_sum += v;
}

inline void delta(size_t i, int64_t v)
{
    size_t j = (n + length - i) % n;
    if(j < overprefix)
        overprefix_sum += v;
    F.delta(j, v);
}

inline int64_t get_suffix(size_t i)
{
    i = min(i, length);
    if(i > overprefix)
        return overprefix_sum + F.get_suffix(i - overprefix);
    else
        return overprefix_sum - F.get_prefix(overprefix - i);
}

void inicjuj(int m) { initialize(m); }
void dodaj(int k) { push_back(k); }
void koryguj(int i, int k) { delta(i, k); }
long long suma(int i) { return get_suffix(i); }

#ifdef XHOVA
#include "roz-driver.cpp"
#endif