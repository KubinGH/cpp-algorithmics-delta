#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 200000;
const size_t TSIZE = 1 << 19;

struct interval_sum_tree
{
    array<uint64_t, TSIZE> values;
    void set_value(uint32_t node, uint64_t value)
    {
        values[node] = value;
        while(node != 1)
        {
            node /= 2;
            values[node] = values[2*node] + values[2*node+1];
        }
    }
    uint64_t find_value(uint32_t node, uint32_t tbegin, uint32_t tend, uint32_t sbegin, uint32_t send)
    {
        if(send < tbegin or tend < sbegin)
            return 0;
        else if(sbegin <= tbegin and tend <= send)
            return values[node];
        else
            return find_value(2*node, tbegin, (tbegin+tend)/2, sbegin, send) +
                   find_value(2*node+1, (tbegin+tend)/2+1, tend, sbegin, send);
    }

    uint64_t find_value(uint32_t sbegin, uint32_t send)
    {
        return find_value(1, 0, TSIZE/2 - 1, sbegin, send);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static interval_sum_tree sum_tree, square_sum_tree;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a;
        cin >> a;
        sum_tree.set_value(TSIZE/2 + i, a);
        square_sum_tree.set_value(TSIZE/2 + i, a*a);
    }
    for(uint32_t mi = 0; mi < m; mi++)
    {
        bool type;
        uint64_t i, j;
        cin >> type >> i >> j;
        if(type == 0)
        {
            i--;
            sum_tree.set_value(TSIZE/2 + i, j);
            square_sum_tree.set_value(TSIZE/2 + i, j*j);
        }
        else
        {
            i--; j--;
            uint64_t a = sum_tree.find_value(i, j),
                     b = square_sum_tree.find_value(i, j);
            cout << (a*a - b)/2 << endl;
        }
    }
}