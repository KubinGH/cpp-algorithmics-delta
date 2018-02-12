#include <bits/stdc++.h>

using namespace std;

typedef uint32_t(*tree_func)(uint32_t a, uint32_t b);

const size_t MAX = 1e6;
const size_t TSIZE = 1 << 21;

uint32_t sum(uint32_t a, uint32_t b)
{
    return a + b;
}
uint32_t max(uint32_t a, uint32_t b)
{
    return a > b ? a : b;
}

template<tree_func F>
struct interval_tree
{
    array<uint64_t, TSIZE> values;
    void set_value(uint32_t i, uint32_t value)
    {
        values[i] = value;
        while(i)
            i = (i - 1) / 2, values[i] = F(values[2*i+1], values[2*i+2]);
    }
    uint32_t find_value(uint32_t i, uint32_t tbegin, uint32_t tend, uint32_t sbegin, uint32_t send)
    {
        if(tend < sbegin or send < tbegin)
            return 0;
        else if(sbegin <= tbegin and tend <= send)
            return values[i];
        else
            return F(find_value(2*i+1, tbegin, (tbegin+tend)/2, sbegin, send),
                     find_value(2*i+2, (tbegin+tend)/2+1, tend, sbegin, send));
    }
    uint32_t find_value(uint32_t sbegin, uint32_t send)
    {
        return find_value(0, 0, TSIZE/2-1, sbegin, send);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    static array<uint64_t, MAX+1> running_sum;
    static interval_tree<max> max_tree;
    for(uint32_t i = 0; i < n; i++)
    {
        uint64_t a;
        cin >> a;
        running_sum[i+1] = running_sum[i] + a;
        max_tree.set_value(i+TSIZE/2-1, a);
    }
    for(uint32_t qi = 0; qi < q; qi++)
    {
        uint32_t i, j;
        cin >> i >> j; i--; j--;
        if(running_sum[j+1] - running_sum[i] > 2 * max_tree.find_value(i, j))
            cout << "TAK\n";
        else
            cout << "NIE\n";
    }
}
