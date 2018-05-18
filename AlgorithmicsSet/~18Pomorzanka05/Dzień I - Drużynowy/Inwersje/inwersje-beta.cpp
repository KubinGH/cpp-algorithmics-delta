#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e5, TSIZE = 1 << 18, MAX_SQRT = 317;

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
        if(sbegin > send) return NONE;
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
uint32_t add_u32(uint32_t a, uint32_t b) { return a + b; }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static uint32_t A[MAX];
    static segment_tree<uint32_t, add_u32, 0, TSIZE> trees[MAX_SQRT], run_tree;
    uint32_t rt = ceil(sqrt(n));
    uint32_t r = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        trees[i/rt].set(A[i], 1);
        run_tree.set(A[i], 1);
        r += run_tree.get(A[i]+1, n);
    }
    auto C = [&](uint32_t i) {
        uint32_t p = 0;
        for(uint32_t c = 0; c < i/rt; c++)
            p += trees[c].get(A[i]+1, n);
        for(uint32_t j = (i/rt)*rt; j < i; j++)
            if(A[j] > A[i])
                p++;
        return p;
    };
    auto AC = [&](uint32_t i) {
        uint32_t p = 0;
        for(uint32_t c = i/rt+1; c < rt; c++)
            p += trees[c].get(0, A[i]-1);
        for(uint32_t j = i; j < (i/rt)*rt; j++)
            if(A[j] < A[i])
                p++;
        return p;
    };
    uint32_t q;
    cin >> q;
    for(uint32_t qi = 0; qi < q; qi++)
    {
        char c;
        cin >> c;
        if(c == 'B')
            cout << r << '\n';
        else if(c == 'A')
        {
            uint32_t a, b;
            cin >> a >> b; a--; b--;
            r -= C(a); r -= C(b);
            r -= AC(a); r -= AC(b);
            trees[a/rt].set(A[a], 0);
            trees[a/rt].set(A[b], 1);
            trees[b/rt].set(A[b], 0);
            trees[b/rt].set(A[a], 1);
            swap(A[a], A[b]);
            r += C(a); r += C(b);
            r += AC(a); r += AC(b);
        }
        cout.flush();
    }
}
