#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 5e5, TSIZE = 1 << 20;

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
uint32_t min_u32(uint32_t a, uint32_t b) { return a < b ? a : b; }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, t;
    cin >> n >> t;
    static segment_tree<uint32_t, max_u32, 0, TSIZE> max_tree;
    static segment_tree<uint32_t, min_u32, -1u, TSIZE> min_tree;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a;
        cin >> a;
        max_tree.set(i, a);
        min_tree.set(i, a);
    }
    for(uint32_t i = 0; i < t; i++)
    {
        uint32_t a, b;
        cin >> a >> b; a--; b--;
        if(b - a == max_tree.get(a, b) - min_tree.get(a, b))
            cout << "TAK";
        else
            cout << "NIE";
        cout << "\n";
    }
}
