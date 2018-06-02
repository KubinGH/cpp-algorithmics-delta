#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e5, TSIZE = 1 << 18, BITS = 8;
const uint8_t NOOP = 0, SET0 = 1,
              SET1 = 3, FLIP = 4;

uint8_t merge_binop(uint8_t a, uint8_t b)
{
    if(b == FLIP)
    {
        if(a == SET0)
            return SET1;
        else if(a == SET1)
            return SET0;
        else if(a == FLIP)
            return NOOP;
        else
            return FLIP;
    }
    else if(b == NOOP)
        return a;
    else
        return b;
}
template<typename T, size_t N, T NONE, typename ST, ST SET_NONE>
struct segment_tree_i
{
    array<T, N> values;
    array<ST, N> to_set;
    static_assert(__builtin_popcount(N) == 1 and N > 4, "N != 2**k");
    size_t offset() const { return N/2 - 1; }
    size_t parent(size_t i) const { return (i - 1) / 2; }
    size_t left(size_t i) const { return 2 * i + 1; }
    size_t right(size_t i) const { return 2 * i + 2; }
    segment_tree_i()
    {
        fill(values.begin() + offset(), values.end(), NONE);
        build();
        fill(to_set.begin(), to_set.end(), SET_NONE);
    }
    void build()
    {
        for(size_t i = offset(); i --> 0;)
            values[i] = values[left(i)] + values[right(i)];
    }
    void pull(size_t i, size_t tbegin, size_t tend)
    {
        if(to_set[i] != SET_NONE)
        {
            if(tbegin < tend)
            {
                to_set[2*i+1] = merge_binop(to_set[2*i+1], to_set[i]);
                to_set[2*i+2] = merge_binop(to_set[2*i+2], to_set[i]);
            }
            if(to_set[i] == FLIP)
                values[i] = (tend - tbegin + 1) - values[i];
            else if(to_set[i] == SET0)
                values[i] = 0;
            else if(to_set[i] == SET1)
                values[i] = (tend - tbegin + 1);
            to_set[i] = SET_NONE;
        }
    }
    void set(size_t i, size_t tbegin, size_t tend,
                       size_t sbegin, size_t send, ST value)
    {
        pull(i, tbegin, tend);
        if(tend < sbegin or send < tbegin)
            return;
        else if(sbegin <= tbegin and tend <= send)
        {
            to_set[i] = merge_binop(to_set[i], value);
            pull(i, tbegin, tend);
        }
        else
        {
            set(left(i),  tbegin, (tbegin+tend)/2, sbegin, send, value);
            set(right(i), (tbegin+tend)/2+1, tend, sbegin, send, value);
            values[i] = values[left(i)] + values[right(i)];
        }
    }
    void set(size_t sbegin, size_t send, ST value)
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
            return get(left(i),  tbegin, (tbegin+tend)/2, sbegin, send) +
                   get(right(i), (tbegin+tend)/2+1, tend, sbegin, send);
    }
    T get(size_t sbegin, size_t send)
        { return get(0, 0, N/2 - 1, sbegin, send); }
};

typedef segment_tree_i<
    uint32_t, TSIZE, 0, uint8_t, NOOP
> binop_tree;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    static binop_tree trees[BITS];
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a;
        cin >> a;
        for(uint32_t j = 0; j < BITS; j++)
        {
            if(a & (1u << j))
                trees[j].values[trees[j].offset()+i] = 1;
        }
    }
    for(uint32_t j = 0; j < BITS; j++)
        trees[j].build();
    for(uint32_t i = 0; i < q; i++)
    {
        char c; uint32_t a, b, v;
        cin >> c >> a >> b;
        if(c == '^' or c == '&' or c == '|')
            cin >> v;
        if(c == '^')
        {
            for(uint32_t j = 0; j < BITS; j++)
                if(v & (1u << j))
                    trees[j].set(a, b, FLIP);
        }
        else if(c == '&')
        {
            for(uint32_t j = 0; j < BITS; j++)
            {
                if((v & (1u << j)) == 0)
                    trees[j].set(a, b, SET0);
            }
        }
        else if(c == '|')
        {
            for(uint32_t j = 0; j < BITS; j++)
            {
                if(v & (1u << j))
                    trees[j].set(a, b, SET1);
            }
        }
        else if(c == '?')
        {
            uint32_t v = 0;
            for(uint32_t j = 0; j < BITS; j++)
                v += trees[j].get(a, b) * (1u << j);
            cout << v << "\n";
        }
    }
}
