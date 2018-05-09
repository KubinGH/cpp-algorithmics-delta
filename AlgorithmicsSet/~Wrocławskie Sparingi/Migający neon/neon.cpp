#include <bits/stdc++.h>
//#define DEBUG

using namespace std;

const size_t MAX = 1 << 17, TSIZE = 1 << 18;
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
    segment_tree()
    {
        fill(values.begin() + TSIZE/2-1, values.begin()+TSIZE, NONEVALUE);
        for(uint32_t i = TSIZE/2-1; i --> 0;)
            values[i] = F(values[2*i+1], values[2*i+2]);
    }
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
#ifdef DEBUG
    srand(time(0));
#endif
    uint32_t n;
    cin >> n;
    unordered_map<uint32_t, uint32_t> M;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a;
        cin >> a;
        M[a] = i;
    }
    auto T = [&](uint32_t a) -> uint32_t {
        auto it = M.find(a);
        if(it != M.end())
            return it->second;
        else
            return n;
    };

    uint32_t m;
    cin >> m;
    static segment_tree<uint32_t, min_u32, 1> grt_tree;
    static array<uint32_t, MAX> A;
    for(uint32_t i = 0; i < m; i++)
    {
        cin >> A[i];
        A[i] = T(A[i]);
    }
    grt_tree.set(m-1, 1);
    for(uint32_t i = 0; i < m - 1; i++)
        grt_tree.set(i, A[i] < A[i+1]);
    auto has_key = [&](uint32_t a, uint32_t b) -> bool {
        return a <= b and b < m and A[a] == 0 and A[b] == n-1 and
               (a == b or grt_tree.get(a, b-1) == 1);
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
        cin >> i >> a;
        i--; a = T(a);
        if(n > m)
        {
            cout << 0 << "\n";
            continue;
        }
        // remove before
        {
            uint32_t b = A[i];
            if(b < n and has_key(i-b, i-b+n-1))
                R--;
        }
        // add next
        {
            A[i] = a;
            if(i < m - 1)
                grt_tree.set(i, A[i] < A[i+1]);
            if(i > 0)
                grt_tree.set(i-1, A[i-1] < A[i]);
            if(a < n and has_key(i-a, i-a+n-1))
                R++;
        }
        cout << R << "\n";
    }
}
