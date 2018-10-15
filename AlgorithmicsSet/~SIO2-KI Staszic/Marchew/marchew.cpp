#include <bits/stdc++.h>
#define MAXF(a, b) ((a) > (b) ? (a) : (b))

using namespace std;

const size_t MAX = 2e5, TSIZE = 1 << 19;
const int32_t INF_I32 = numeric_limits<int32_t>::max()-1;

// function templates were optimized away
template<typename T, size_t N, T NONE, T SET_NONE>
struct segment_tree_intervalop
{
    uint32_t _id;
    array<T, N> values, to_set;
    static_assert(__builtin_popcount(N) == 1 and N > 4, "N != 2**k");
    inline size_t offset() const { return N/2 - 1; }
    segment_tree_intervalop()
    {
        fill(values.begin() + offset(), values.end(), NONE);
        for(size_t i = offset(); i --> 0;)
            values[i] = MAXF(values[2*i+1], values[2*i+2]);
        fill(to_set.begin(), to_set.end(), SET_NONE);
    }
    inline void pull(size_t i, size_t tbegin, size_t tend)
    {
        if(to_set[i] != SET_NONE)
        {
            if(values[i] != -INF_I32) values[i] += to_set[i];
            if(tbegin < tend)
            {
                to_set[2*i+1] += to_set[i];
                to_set[2*i+2] += to_set[i];
            }
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
            to_set[i] += value;
            pull(i, tbegin, tend);
        }
        else
        {
            set(2*i+1, tbegin, (tbegin+tend)/2, sbegin, send, value);
            set(2*i+2, (tbegin+tend)/2+1, tend, sbegin, send, value);
            values[i] = MAXF(values[2*i+1], values[2*i+2]);
        }
    }
    void set(size_t sbegin, size_t send, T value)
        { return set(0, 0, N/2 - 1, sbegin, send, value); }
    size_t find_extrem_pos(bool set_too = false, T svalue = 0)
    {
        size_t i = 0, tbegin = 0, tend = N/2 - 1;
        pull(i, tbegin, tend);
        T value = values[0];
        while(tbegin < tend)
        {
            pull(2*i+1, tbegin, (tbegin+tend)/2);
            pull(2*i+2, (tbegin+tend)/2+1, tend);
            if(values[2*i+1] == value)
                i = 2*i+1, tend = (tbegin+tend)/2;
            else
                i = 2*i+2, tbegin = (tbegin+tend)/2+1;
        }
        if(set_too)
        {
            size_t ri = i;
            values[i] = svalue;
            while(i > 0)
            {
                i = (i - 1) / 2;
                values[i] = MAXF(values[2*i+1], values[2*i+2]);
            }
            i = ri;
        }
        return i;
    }
    void set_single(size_t i, T value)
    {
        size_t j = 0, tbegin = 0, tend = N/2 - 1;
        while(tbegin < tend)
        {
            pull(j, tbegin, tend);
            if(i-offset() <= (tbegin+tend)/2)
                j = 2*j+1, tend = (tbegin+tend)/2;
            else
                j = 2*j+2, tbegin = (tbegin+tend)/2+1;
        }
        pull(i, tbegin, tend);
        values[i] = value;
        uint32_t f = 1;
        while(i > 0)
        {
            if(i % 2 == 0)
                tbegin -= f;
            else
                tend += f;
            f *= 2;
            i = (i - 1) / 2;
            pull(2*i+1, tbegin, (tbegin+tend)/2);
            pull(2*i+2, (tbegin+tend)/2+1, tend);
            values[i] = MAXF(values[2*i+1], values[2*i+2]);
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    static segment_tree_intervalop<int32_t, TSIZE, -INF_I32, 0> tree[2];
    tree[0]._id = 0; tree[1]._id = 1;
    uint32_t n, m; int32_t g1, g2;
    cin >> n >> m >> g1 >> g2;
    uint32_t r1 = 0, r2 = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        int32_t a;
        cin >> a;
        if(a < g2)
        {
            uint32_t p = a >= g1;
            tree[p].set_single(tree[p].offset() + i, a);
            tree[!p].set_single(tree[p].offset() + i, -INF_I32);
            if(a >= g1) r1++;
        }
        else
            r2++;
    }
    for(uint32_t mi = 0; mi < m; mi++)
    {
        uint32_t a, b; int32_t x;
        cin >> a >> b >> x; a--; b--;
        tree[0].set(a, b, x);
        tree[1].set(a, b, x);
        if(g1 > 0) g1--;
        if(g2 > 0) g2--;
        while(tree[0].values[0] >= g1)
        {
            int32_t v = tree[0].values[0];
            uint32_t i = tree[0].find_extrem_pos(true, -INF_I32);
            if(v < g2)
            {
                tree[1].set_single(i, v);
                r1++;
            }
            else
                r2++;
        }
        while(tree[1].values[0] >= g2)
        {
            tree[1].find_extrem_pos(true, -INF_I32);
            r2++;
            r1--;
        }
        cout << r2 << " " << r1 << "\n";
    }
}
