#include <bits/stdc++.h>

using namespace std;


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
    // iterative
    T get(size_t sbegin, size_t send)
    {
        send++;
        size_t result = NONE;
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

uint32_t xor_u32(uint32_t a, uint32_t b) { return a ^ b; }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    static segment_tree<uint32_t, xor_u32, 0, 1 << 20> tree;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a;
        cin >> a;
        tree.set(i, a);
    }
    for(uint32_t qi = 0; qi < q; qi++)
    {
        string com;
        cin >> com;
        uint32_t i, j;
        cin >> i >> j; i--; j--;
        if(com == "czytaj")
            cout << tree.get(i, j) << '\n';
        else if(com == "zamien")
        {
            uint32_t a = tree[i], b = tree[j];
            tree.set(j, a);
            tree.set(i, b);
        }
    }
}
