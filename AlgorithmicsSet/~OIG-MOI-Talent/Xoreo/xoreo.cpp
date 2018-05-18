#include <bits/stdc++.h>
#ifdef _WIN32
#define LLU_FMT "%I64u"
#else
#define LLU_FMT "%llu"
#endif

using namespace std;

typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;

const size_t BITS_E = 20, TSIZE = 1 << 18;
const size_t MAX = 1e5;

template<typename T, size_t N>
struct arrayk
{
    T _A[N], *_AP;
    arrayk() { _AP = _A; }
    T* begin() { return _AP; }
    T* end() { return _AP + N; }
    T& operator[] (size_t i) { return _A[i]; }
};

template<typename T, T(*F)(T, T), T NONE, size_t N, T SET_NONE,
        void(*P)(size_t, size_t, size_t, arrayk<T, N>&, arrayk<T, N>&)>
struct segment_tree_intervalop
{
    arrayk<T, N> values, to_set;
    size_t offset() const { return N/2 - 1; }
    size_t parent(size_t i) const { return (i - 1) / 2; }
    size_t left(size_t i) const { return 2 * i + 1; }
    size_t right(size_t i) const { return 2 * i + 2; }
    segment_tree_intervalop()
    {
        fill(values.begin() + offset(), values.end(), NONE);
        build();
    }
    void build()
    {
        for(size_t i = offset(); i --> 0;)
            values[i] = F(values[left(i)], values[right(i)]);
        fill(to_set.begin(), to_set.end(), SET_NONE);
    }
    void pull(size_t i, size_t tbegin, size_t tend)
    {
        if(to_set[i] == SET_NONE)
            return;
        P(i, tbegin, tend, values, to_set);
        to_set[i] = SET_NONE;
    }
    void set(size_t i, size_t tbegin, size_t tend,
                       size_t sbegin, size_t send, T value)
    {
        pull(i, tbegin, tend);
        if(tend < sbegin or send < tbegin)
            return;
        else if(sbegin <= tbegin and tend <= send)
        {
            to_set[i] = F(to_set[i], value);
            pull(i, tbegin, tend);
        }
        else
        {
            set(left(i),  tbegin, (tbegin+tend)/2, sbegin, send, value);
            set(right(i), (tbegin+tend)/2+1, tend, sbegin, send, value);
            values[i] = F(values[left(i)], values[right(i)]);
        }
    }
    void set(size_t sbegin, size_t send, T value)
        { return set(0, 0, N/2 - 1, sbegin, send, value); }
    T get(size_t i, size_t tbegin, size_t tend,
                    size_t sbegin, size_t send)
    {
        pull(i, tbegin, tend);
        if(tend < sbegin or send < tbegin)
            return NONE;
        else if(sbegin <= tbegin and tend <= send)
            return values[i];
        else
            return F(get(left(i),  tbegin, (tbegin+tend)/2, sbegin, send),
                     get(right(i), (tbegin+tend)/2+1, tend, sbegin, send));
    }
    T get(size_t sbegin, size_t send)
        { return get(0, 0, N/2 - 1, sbegin, send); }
};

uint32_t add_u32(uint32_t a, uint32_t b) { return a + b; }

void pull_toggle(size_t i, size_t tbegin, size_t tend,
                 arrayk<uint32_t, TSIZE>& values,
                 arrayk<uint32_t, TSIZE>& to_set)
{
    if(tbegin < tend)
    {
        to_set[2*i+1] ^= 1;
        to_set[2*i+2] ^= 1;
    }
    values[i] = (tend - tbegin + 1) - values[i];
}

int main()
{
    static segment_tree_intervalop<
        uint32_t, add_u32, 0, TSIZE,
        0, pull_toggle
    > bit_count_trees[BITS_E];
    uint32_t n, q;
    scanf("%u %u", &n, &q);
    static arrayk<uint32_t, MAX> base;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> base[i];
        for(uint32_t b = 0; b < BITS_E; b++)
        {
            if(base[i] & (1u << b))
            {
                bit_count_trees[b].values[bit_count_trees[b].offset() + i] = 1;
                //cerr << "1 x" << (1u<<b) << " bit @ " << i << endl;
            }
        }
    }
    for(uint32_t b = 0; b < BITS_E; b++)
        bit_count_trees[b].build();
    for(uint32_t qi = 0; qi < q; qi++)
    {
        uint32_t i, j, v;
        scanf("%u %u %u", &i, &j, &v); i--; j--;
        if(v == 0)
        {
            uint64_t r = 0;
            for(uint32_t b = 0; b < BITS_E; b++)
            {
                //cerr << bit_count_trees[b].get(i, j) << " x" << (1llu << b) << endl;
                r += (1llu << b) * bit_count_trees[b].get(i, j);
            }
            printf(LLU_FMT"\n", r);
        }
        else
        {
            for(uint32_t b = 0; b < BITS_E; b++)
            {
                if(v & (1u << b))
                    bit_count_trees[b].set(i, j, 1);
            }
        }
    }
}
