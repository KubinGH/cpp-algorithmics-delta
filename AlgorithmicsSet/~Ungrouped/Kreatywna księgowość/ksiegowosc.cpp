#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e5, TSIZE = 1<<18;
const int64_t LIM = 1e9;

template<typename T, T(*F)(T, T), T NONE, size_t N, T SET_NONE,
        void(*P)(size_t, size_t, size_t, array<T, N>&, array<T, N>&)>
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
        fill(to_set.begin(), to_set.end(), SET_NONE);
        build();
    }
    void build()
    {
        for(size_t i = offset(); i --> 0;)
            values[i] = F(values[left(i)], values[right(i)]);
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

int64_t max_i64(int64_t a, int64_t b) { return a > b ? a : b; }
int64_t min_i64(int64_t a, int64_t b) { return a < b ? a : b; }
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
    uint32_t n;
    cin >> n;
    segment_tree_intervalop<int64_t, min_i64, 1llu << 60, TSIZE, 0, pull_add> min_tree;
    segment_tree_intervalop<int64_t, max_i64, 1llu << 60, TSIZE, 0, pull_add> max_tree;
    uint32_t r = 0;
    int64_t* A = &max_tree.values[max_tree.offset()];
    for(uint32_t i = 0; i < n; i++)
    {
        int64_t a;
        cin >> a;
        min_tree.values[i + min_tree.offset()] = a;
        max_tree.values[i + max_tree.offset()] = a;
        if(i > 0 and A[i] > A[i-1])
            r++;
    }
    uint32_t q;
    cin >> q;
    for(uint32_t i = 0; i < q; i++)
    {
        uint32_t a, b; int64_t d;
        cin >> a >> b >> d; a--; b--;
        bool ag = a > 0 and A[a] > A[a-1],
             bg = b < n - 1 and A[b+1] > A[b];
        min_tree.set(a, b, d);
        max_tree.set(a, b, d);
        if(min_tree.get(0, n-1) < 0 or max_tree.get(0, n-1) > LIM)
        {
            min_tree.set(a, b, -d);
            max_tree.set(a, b, -d);
            cout << -1;
            continue;
        }
        if(ag and A[a] <= A[a-1])
            r--;
        else if(not ag and A[a] > A[a-1]);

    }

}
