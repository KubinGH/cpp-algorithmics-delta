#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e6, TSIZE = 1 << 21;

template<typename T, size_t N, T(*F)(T, T), T NONE,
        void(*P)(size_t, size_t, size_t, array<T, N>&, array<T, N>&), T SET_NONE,
        T(*S)(T, T) = F>
struct segment_tree_intervalop
{
    array<T, N> values, to_set;
    static_assert(__builtin_popcount(N) == 1 and N > 4, "N != 2**k");
    size_t offset() const { return N/2 - 1; }
    size_t parent(size_t i) const { return (i - 1) / 2; }
    size_t left(size_t i) const { return 2 * i + 1; }
    size_t right(size_t i) const { return 2 * i + 2; }
    segment_tree_intervalop()
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
};
int64_t max_i64(int64_t a, int64_t b) { return a>b ? a : b; }
int64_t add_i64(int64_t a, int64_t b) { return a + b; }
void pull_add(size_t i, size_t tbegin, size_t tend,
              array<int64_t, TSIZE>& values,
              array<int64_t, TSIZE>& to_set)
{
    if(tbegin < tend)
    {
        to_set[2*i+1] += to_set[i];
        to_set[2*i+2] += to_set[i];
    }
    values[i] += to_set[i];
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static uint32_t id[MAX];
    for(uint32_t i = 0; i < n; i++)
        cin >> id[i], id[i]--;
    static int64_t value[MAX];
    for(uint32_t i = 0; i < m; i++)
        cin >> value[i];
    static segment_tree_intervalop<
        int64_t, TSIZE, max_i64, 0, pull_add, 0, add_i64
    > result_tree;
    static pair<uint32_t, uint32_t> last_segment[MAX];
    for(uint32_t i = 0; i < m; i++)
        last_segment[i] = make_pair(n, n);
    int64_t result = 0;
    for(uint32_t i = n; i --> 0; )
    {
        uint32_t j, k;
        tie(j, k) = last_segment[id[i]];
        result_tree.set(j, k, -value[id[i]]);
        result_tree.set(i, j-1, value[id[i]]);
        last_segment[id[i]] = make_pair(i, j-1);
        result = max(result, result_tree.values[0]);
    }
    cout << result;
}
