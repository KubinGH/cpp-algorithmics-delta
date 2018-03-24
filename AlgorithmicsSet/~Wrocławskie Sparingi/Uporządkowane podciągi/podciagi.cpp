#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500000, TSIZE = 1 << 20;
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

template<tree_func F, uint32_t NONEVALUE>
struct interval_tree
{
    array<uint32_t, TSIZE> values;
    void set_value(uint32_t i, uint32_t value)
    {
        i += TSIZE/2 - 1;
        values[i] = value;
        while(i > 0)
            i--, i /= 2, values[i] = F(values[2*i+1], values[2*i+2]);
    }
    uint32_t find_value(uint32_t i, uint32_t tbegin, uint32_t tend, uint32_t sbegin, uint32_t send)
    {
        if(tend < sbegin or send < tbegin)
            return NONEVALUE;
        else if(sbegin <= tbegin and tend <= send)
            return values[i];
        else
            return F(find_value(2*i+1, tbegin, (tbegin+tend)/2, sbegin, send),
                     find_value(2*i+2, (tbegin+tend)/2+1, tend, sbegin, send));
    }
    uint32_t find_value(uint32_t sbegin, uint32_t send)
    {
        //return find_value(0, 0, TSIZE/2-1, sbegin, send);
        send++;
        uint32_t result = NONEVALUE;
        for(sbegin += TSIZE/2 - 1, send += TSIZE/2 - 1; sbegin < send; sbegin--, sbegin /= 2, send--, send /= 2)
        {
            if(sbegin % 2 == 0) result = F(result, values[sbegin++]);
            if(send % 2 == 0)   result = F(result, values[--send]);
        }
        return result;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    static interval_tree<min_u32, -1u> min_tree, nxt_tree;
    static interval_tree<max_u32, 0> max_tree;
    static array<uint32_t, MAX> A;
    unordered_map<uint32_t, uint32_t> M;
    M.reserve(n);
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a;
        cin >> a;
        min_tree.set_value(i, a);
        max_tree.set_value(i, a);
        A[i] = a;
    }
    for(uint32_t i = n; i --> 0; )
    {
        if(M.find(A[i]) != M.end())
            nxt_tree.set_value(i, M[A[i]]);
        else
            nxt_tree.set_value(i, n);
        M[A[i]] = i;
    }
    for(uint32_t i = 0; i < q; i++)
    {
        uint32_t a, b;
        cin >> a >> b; a--; b--;
        uint32_t x = min_tree.find_value(a, b), y = max_tree.find_value(a, b);
        uint32_t z = nxt_tree.find_value(a, b);
        //cout << x << " " << y << " " << s << endl;
        if(y - x == b - a and z > b)
            cout << "TAK\n";
        else
            cout << "NIE\n";
        //cout.flush();
    }
}
