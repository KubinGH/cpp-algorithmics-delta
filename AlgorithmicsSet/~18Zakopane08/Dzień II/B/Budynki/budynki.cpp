#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 17, TSIZE = 1 << 18;

template<typename T, size_t N, T(*F)(T, T), T NONE>
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
        { return values[offset() + i]; }
};
uint32_t add_u32(uint32_t a, uint32_t b) { return a + b; }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    static uint32_t A[MAX];
    static segment_tree<uint32_t, TSIZE, add_u32, 0> tree;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    auto fulfills = [&](uint32_t i) {
        return i <= n - 3 and A[i] < A[i+1] and A[i] < A[i+2] and A[i+1] > A[i+2];
    };
    for(uint32_t i = 0; i < n - 2; i++)
        tree.set(i, fulfills(i));
    while(k --> 0)
    {
        uint32_t a, b, c;
        cin >> a >> b >> c; b--;
        if(a == 1)
        {
            c--;
            if(c - b + 1 >= 3)
                cout << tree.get(b, c - 2) << "\n";
            else
                cout << 0 << "\n";
        }
        else if(a == 2)
        {
            A[b] = c;
            for(uint32_t i = 0; i < 3 and i <= b; i++)
                tree.set(b-i, fulfills(b-i));
        }
    }
}
