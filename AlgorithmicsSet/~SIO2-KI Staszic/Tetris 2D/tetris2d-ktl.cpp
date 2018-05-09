#include <bits/stdc++.h>

using namespace std;

const size_t TSIZE = 1 << 21;
template<typename T, T(*F)(T, T), T NONE, size_t N, T SET_NONE,
        void(*P)(size_t, size_t, size_t, array<T, N>&, array<T, N>&)>
struct segment_tree_intervalop
{
    array<T, N> values, to_set;
    static_assert(__builtin_popcount(N) == 1 and N > 4, "N != 2**k");
    static size_t offset() { return N/2 - 1; }
    static size_t parent(size_t i) { return (i - 1) / 2; }
    static size_t left(size_t i) { return 2 * i + 1; }
    static size_t right(size_t i) { return 2 * i + 2; }
    segment_tree_intervalop()
    {
        fill(values.begin() + offset(), values.end(), NONE);
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
            to_set[i] = max(to_set[i], value);
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

void pull_max(size_t i, size_t tbegin, size_t tend,
              array<uint32_t, TSIZE>& values,
              array<uint32_t, TSIZE>& to_set)
{
    if(tbegin < tend)
    {
        to_set[2*i+1] = max(to_set[2*i+1], to_set[i]);
        to_set[2*i+2] = max(to_set[2*i+2], to_set[i]);
    }
    values[i] = max(to_set[i], values[i]);
}
uint32_t max_u32(uint32_t a, uint32_t b) { return a > b ? a : b; }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t w, n;
    cin >> w >> n;
    static segment_tree_intervalop<uint32_t, max_u32, 0, TSIZE,
                                   0, pull_max> tree;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t l, x;
        cin >> l >> x;
        uint32_t v = tree.get(x, x+l-1);
        tree.set(x, x+l-1, v + 1);
    }
    cout << tree.values[0];
}
