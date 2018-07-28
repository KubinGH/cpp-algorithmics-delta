#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 3e5, TSIZE = 1 << 20;

template<typename T, size_t N, T(*F)(T, T), T NONE,
        void(*P)(size_t, size_t, size_t, array<T, N>&, array<T, N>&), T SET_NONE,
        T(*S)(T, T) = F>
struct segment_tree_i
{
    array<T, N> values, to_set;
    static_assert((N&(N-1))==0 and N > 4, "N != 2**k");
    size_t offset() const { return N/2 - 1; }
    size_t parent(size_t i) const { return (i - 1) / 2; }
    size_t left(size_t i) const { return 2 * i + 1; }
    size_t right(size_t i) const { return 2 * i + 2; }
    segment_tree_i()
    {
        fill(values.begin() + offset(), values.end(), NONE);
        for(size_t i = offset(); i --> 0;)
            values[i] = F(values[left(i)], values[right(i)]);
        fill(to_set.begin(), to_set.end(), SET_NONE);
    }
    void pull(size_t i, size_t tbegin, size_t tend)
    {
        if(to_set[i] != SET_NONE)
        {
            P(i, tbegin, tend, values, to_set);
            to_set[i] = SET_NONE;
        }
    }
    void set(size_t i, size_t tbegin, size_t tend,
                       size_t sbegin, size_t send, T value)
    {
        pull(i, tbegin, tend);
        if(tend < sbegin or send < tbegin)
            return;
        else if(sbegin <= tbegin and tend <= send)
        {
            to_set[i] = S(to_set[i], value);
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
    T get(size_t i) { return get(i, i); }
};

uint32_t max_u32(uint32_t a, uint32_t b) { return a>b ? a : b; }
void pull_set_max(size_t i, size_t tbegin, size_t tend,
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

typedef segment_tree_i<
    uint32_t, 1u << 20, max_u32, 0u, pull_set_max, 0u
> tree_t;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    static tree_t tree;
    while(q --> 0)
    {
        uint32_t i, j, a; cin >> i >> j >> a;
        tree.set(i, j, a);
    }
    static uint32_t A[MAX]; fill(A, A + n, -1u);
    set<uint32_t> free;
    for(uint32_t i = 0; i < n; i++) free.insert(i);
    bool ok = true;
    for(uint32_t i = 0; i < n and ok; i++)
    {
        auto it = free.lower_bound(tree.get(i));
        if(it != free.end())
            A[i] = *it, free.erase(it);
        else
            ok = false;
    }
    if(ok) for(uint32_t i = 0; i < n; i++)
        cout << A[i] << " ";
    else
        cout << -1;
}
