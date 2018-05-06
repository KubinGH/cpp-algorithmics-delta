#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 2e5, TSIZE = 1 << 18;
typedef uint32_t(*tree_func)(uint32_t, uint32_t);

uint32_t min_u32(uint32_t a, uint32_t b)
{
    return a < b ? a : b;
}
uint32_t max_u32(uint32_t a, uint32_t b)
{
    return a > b ? a : b;
}
uint32_t add_u32(uint32_t a, uint32_t b)
{
    return a + b;
}

template<typename T, tree_func F, T NONEVALUE>
struct segment_tree
{
    array<T, TSIZE> values;
    void set(uint32_t i, T value)
    {
        i += TSIZE/2 - 1;
        values[i] = value;
        while(i > 0)
            i--, i /= 2, values[i] = F(values[2*i+1], values[2*i+2]);
    }
    T get(uint32_t i, uint32_t tbegin, uint32_t tend,
                      uint32_t sbegin, uint32_t send)
    {
        if(tend < sbegin or send < tbegin)
            return NONEVALUE;
        else if(sbegin <= tbegin and tend <= send)
            return values[i];
        else
            return F(get(2*i+1, tbegin, (tbegin+tend)/2, sbegin, send),
                     get(2*i+2, (tbegin+tend)/2+1, tend, sbegin, send));
    }
    T get(uint32_t sbegin, uint32_t send)
        { return get(0, 0, TSIZE/2-1, sbegin, send); }
};

int main()
{
    uint32_t n;
    cin >> n;
    unordered_map<uint32_t, uint64_t> M;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a;
        cin >> a;
        M[a] = i;
    }
    auto T = [&](uint32_t a) -> uint64_t {
        auto it = M.find(a);
        if(it != M.end())
            return it->second;
        else
            return n;
    };


    uint32_t m;
    cin >> m;
    static segment_tree<uint64_t, min_u32, numeric_limits<uint64_t>::max()>
                min_tree, nxt_tree;
    static segment_tree<uint64_t, max_u32, 0> max_tree;
    static array<uint64_t, MAX> A;
    static array<uint32_t, MAX> prev;
    for(uint32_t i = 0; i < m; i++)
    {
        cin >> A[i];
        A[i] = T(A[i]);
        min_tree.set(i, A[i]); max_tree.set(i, A[i]);
    }
    unordered_map<uint64_t, uint32_t> seen;
    static array<set<uint32_t>, MAX> all_seen;
    for(uint32_t i = m; i --> 0;)
    {
        auto it = seen.find(A[i]);
        prev[i] = -1u;
        if(it != seen.end())
        {
            nxt_tree.set(i, it->second);
            prev[it->second] = i;
        }
        else
            nxt_tree.set(i, m);
        seen[A[i]] = i;
    }
    for(uint32_t i = 0; i < m; i++)
        all_seen[A[i]].insert(i);
    auto has_key = [&](uint32_t a, uint32_t b) -> bool {
        //cout << "try " << a << ".." << b << ": " <<
        //    min_tree.get(a, b) << " " << max_tree.get(a, b) << " " <<
        //    nxt_tree.get(a, b) << endl;
        return min_tree.get(a, b) == 0 and max_tree.get(a, b) == n-1 and
               nxt_tree.get(a, b) > b;
    };
    uint32_t R = 0;
    if(n <= m) for(uint32_t i = 0; i < m - n + 1; i++)
    {
        if(has_key(i, i + n - 1))
        {
            R++;
            i += n - 1;
        }
    }

    uint32_t q;
    cin >> q;
    for(uint32_t qi = 0; qi < q; qi++)
    {
        uint32_t i, a;
        cin >> i >> a; i--; a = T(a);
        cout << R << endl;
    }
}
