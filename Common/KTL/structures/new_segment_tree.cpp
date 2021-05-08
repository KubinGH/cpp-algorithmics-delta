#include <vector>
#include <cstddef>
#include <algorithm>

using std::size_t;
using std::vector;
using std::__lg;

template<typename T, typename Monoid>
struct segment_tree
{
    size_t w;
    const T identity;
    vector<T> values;
    Monoid f;

    segment_tree(size_t n, T id = {}, Monoid _f = {})
        : w(1 << __lg(2*n - 1)), identity(id), values(2*w, id), f(_f) {}

    void build()
    {
        for(size_t j = w; j --> 1; )
            values[j] = f(values[2*j], values[2*j+1]);
    }
    template<typename It>
    void build(It first, It last)
    {
        copy(first, last, values.begin() + w);
        build();
    }

    void set(size_t p, T v)
    {
        values[p += w] = v;
        while(p /= 2)
            values[p] = f(values[2*p], values[2*p + 1]);
    }

    T get(size_t l, size_t r) const
    {
        T a = identity, b = identity;
        for(l += w, r += w; l < r; l /= 2, r /= 2)
        {
            if(l % 2) a = f(a, values[l++]);
            if(r % 2) b = f(values[--r], b);
        }
        return f(a, b);
    }

    T get() const
    {
        return values[1];
    }
};
