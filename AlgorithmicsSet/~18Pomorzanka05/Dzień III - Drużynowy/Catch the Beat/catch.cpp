#include <bits/stdc++.h>

using namespace std;

typedef pair<int32_t, int32_t> pair_i32;

const size_t MAX = 1e6;
const int32_t TSIZE = 1<<21;

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
uint32_t max_u32(uint32_t a, uint32_t b) { return a > b ? a : b; }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    static pair_i32 A[MAX];
    for(uint32_t i = 0; i < n; i++)
    {
        int32_t x, y;
        cin >> x >> y;
        if(y < x)
        {
            i--, n--;
            continue;
        }
        A[i].first = x - y;
        A[i].second = -(x + y);
    }
    sort(A, A + n);
    static segment_tree<uint32_t, max_u32, 0, TSIZE> tree;
    for(uint32_t i = n; i --> 0;)
    {
        uint32_t x = -A[i].second;
        tree.set(x, tree.get(0, x) + 1);
    }
    cout << tree.values[0];
}
