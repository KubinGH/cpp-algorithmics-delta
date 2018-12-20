#include <bits/stdc++.h>

using namespace std;

// Set on interval - sum on interval
template<typename T, size_t N>
struct segment_tree_set_sum
{
    // width, height
    size_t w, h;

    // current values and mutations to take
    vector<T> values, mutate;
    vector<bool> lazy; // flag if children have yet to receive the mutation

    segment_tree_set_sum(size_t n)
    {
        h = 32 - __builtin_clz(2*n-1);
        w = 1 << (h-1);
        values.resize(2*w); mutate.resize(2*w); lazy.resize(2*w);
        fill(lazy.begin(), lazy.end(), true);
    }
    // recalculate value for node `p`
    void calc_value(size_t p, size_t length)
    {
        if(not lazy[p]) values[p] = values[2*p] + values[2*p+1];
        else values[p] = mutate[p] * length;
    }
    // recalculate value (and maybe flag a mutation) for node `p`
    void queue_mutation(size_t p, T value, size_t length)
    {
        values[p] = value * length;
        if(p < w) mutate[p] = value, lazy[p] = true;
    }

    // push down all mutations on the nodes containing [l, r)
    void push_all(size_t l, size_t r)
    {
        size_t s = h, k = 1 << (h-1);
        for(l += w, r += w-1; s > 0; s--, k /= 2)
        {
            for(size_t i = l >> s; i <= r >> s; i++) if(lazy[i])
            {
                queue_mutation(2*i, mutate[i], k);
                queue_mutation(2*i+1, mutate[i], k);
                lazy[i] = false;
            }
        }
    }

    // recalculate all values in [l, r)
    void calc_values(size_t l, size_t r)
    {
        size_t k = 2;
        for(l += w, r += w-1; l > 1; k *= 2)
        {
            l /= 2; r /= 2;
            for(size_t i = r; i >= l; i--)
                calc_value(i, k);
        }
    }

    void modify(size_t l, size_t r, T value)
    {
        if(value == 0) return;
        push_all(l, l + 1);
        push_all(r - 1, r);
        int l0 = l, r0 = r, k = 1;
        for(l += w, r += w; l < r; l /= 2, r /= 2, k *= 2)
        {
            if(l % 2) queue_mutation(l++, value, k);
            if(r % 2) queue_mutation(--r, value, k);
        }
        calc_values(l0, l0 + 1);
        calc_values(r0 - 1, r0);
    }
    size_t query(size_t l, size_t r)
    {
        push_all(l, l + 1);
        push_all(r - 1, r);
        T result = 0;
        for(l += w, r += w; l < r; l /= 2, r /= 2)
        {
            if(l % 2) result += values[l++];
            if(r % 2) result += values[--r];
        }
        return result;
    }
};


int main()
{
    uint32_t n;
    cin >> n;
    static segment_tree_set_sum<int, 1<<20> tree(n);
    char c; uint32_t a, b;
    while(cin >> c >> a >> b)
    {
        if(c == '=')
        {
            int v;
            cin >> v;
            tree.modify(a, b, v);
        }
        else if(c == '+')
            cout << tree.query(a, b) << endl;
    }
}
