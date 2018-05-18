#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e6, TSIZE = 1u << 22;

template<typename T, T(*F)(T, T), T NONE, size_t N>
struct segment_tree
{
    array<T, N> values;
    static_assert(__builtin_popcount(N) == 1 and N > 4, "N != 2**k");
    size_t offset() const { return N/2 - 1; }
    size_t parent(size_t i) const { return (i - 1) / 2; }
    size_t left(size_t i) const { return 2 * i + 1; }
    size_t right(size_t i) const { return 2 * i + 2; }
    segment_tree()
    {
        fill(values.begin() + offset(), values.end(), NONE);
        for(size_t i = offset(); i --> 0;)
            values[i] = F(values[left(i)], values[right(i)]);
    }
    void set(size_t i, T value)
    {
        i += offset();
        values[i] = value;
        while(i > 0)
            i = parent(i), values[i] = F(values[left(i)], values[right(i)]);
    }
    T get(size_t sbegin, size_t send)
    {
        send++;
        T result = NONE;
        for(sbegin += offset(), send += offset(); sbegin < send;
            sbegin = parent(sbegin), send = parent(send))
        {
            if(sbegin % 2 == 0) result = F(result, values[sbegin++]);
            if(send % 2 == 0)   result = F(result, values[--send]);
        }
        return result;
    }
    const T& operator[] (size_t i) const
    {
        return values[offset() + i];
    }
};
uint64_t max_u64(uint64_t a, uint64_t b) { return (a>b) ? a : b; }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, t;
    cin >> n >> t;
    static uint32_t A[MAX], B[MAX];
    static uint64_t C[MAX];
    static pair<uint32_t, uint32_t> E[2*MAX];
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i] >> B[i] >> C[i];
        E[2*i] = make_pair(A[i], 2*i);
        E[2*i+1] = make_pair(B[i], 2*i+1);
    }
    sort(E, E + 2*n);
    for(uint32_t i = 0, f = 0; i < 2*n; i++)
    {
        if(i > 0 and E[i-1].first == E[i].first)
            f++;
        if(E[i].second % 2 == 0)
            A[E[i].second/2] = i - f;
        else
            B[E[i].second/2] = i - f;
    }
    for(uint32_t i = 0; i < n; i++)
        E[i] = make_pair(B[i], i);
    sort(E, E + n);
    static segment_tree<uint64_t, max_u64, 0, TSIZE> result_tree;
    for(uint32_t e = 0; e < n; e++)
    {
        uint32_t i = E[e].second;
        uint64_t p = result_tree.get(0, A[i]) + C[i];
        if(p > result_tree[B[i]])
            result_tree.set(B[i], p);
    }
    cout << result_tree.values[0];
}
