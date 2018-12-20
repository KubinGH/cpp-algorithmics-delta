#include <bits/stdc++.h>

using namespace std;

// Set on interval - sum on interval
template<typename T>
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

    void mut(size_t l, size_t r, T value)
    {
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
    T get(size_t l, size_t r)
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

struct query_t
{
    uint32_t L, R; bool t;
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    vector<int32_t> A(n);
    for(uint32_t i = 0; i < n; i++)
    {
        int32_t a;
        cin >> a;
        A[i] = a;
    }
    vector<query_t> queries(q);
    for(uint32_t i = 0; i < q; i++)
    {
        cin >> queries[i].L >> queries[i].R >> queries[i].t;
        queries[i].L--; queries[i].R--;
    }
    vector<int32_t> E(A.begin(), A.end());
    sort(E.begin(), E.end());
    E.erase(unique(E.begin(), E.end()), E.end());
    uint32_t lo = 0, hi = E.size();
    segment_tree_set_sum<uint32_t> T(n);
    while(lo < hi)
    {
        uint32_t mid = (lo + hi) / 2;
        for(uint32_t i = 0; i < n; i++)
        {
            if(A[i] > E[mid])
                T.values[T.w + i] = 1;
            else
                T.values[T.w + i] = 0;
        }
        for(uint32_t i = T.w; i --> 1; )
            T.values[i] = T.values[2*i] + T.values[2*i+1];
        fill(T.mutate.begin(), T.mutate.end(), 0);
        fill(T.lazy.begin(), T.lazy.end(), false);
        for(uint32_t i = 0; i < q; i++)
        {
            uint32_t L = queries[i].L, R = queries[i].R; bool t = queries[i].t;
            uint32_t c = T.get(L, R+1);
            if(t == 0)
            {
                c = (R - L + 1) - c;
                T.mut(L, L+c, 0);
                T.mut(L+c, R+1, 1);
            }
            else
            {
                T.mut(L, L+c, 1);
                T.mut(L+c, R+1, 0);
            }
        }
        if(T.get(n/2, n/2+1) == 0)
            hi = mid;
        else
            lo = mid+1;
    }
    cout << E[lo];
}
