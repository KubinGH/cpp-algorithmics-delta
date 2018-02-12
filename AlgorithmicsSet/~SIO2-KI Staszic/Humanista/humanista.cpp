#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500000;
const size_t TSIZE = 1048576;

struct xor_tree
{
    array<uint32_t, TSIZE> values;
    void set_value(uint32_t node, uint32_t value)
    {
        values[node] = value;
        while(node != 1)
        {
            node /= 2;
            values[node] = values[node*2] ^ values[node*2+1];
        }
    }

    uint32_t find_value(uint32_t node, uint32_t tbegin, uint32_t tend, uint32_t sbegin, uint32_t send)
    {
        if(tend < sbegin or send < tbegin)
            return 0;
        else if(sbegin <= tbegin and tend <= send)
            return values[node];
        else
            return find_value(node*2, tbegin, (tbegin+tend)/2, sbegin, send) ^
                   find_value(node*2+1, (tbegin+tend)/2+1, tend, sbegin, send);
    }
    uint32_t find_value(uint32_t sbegin, uint32_t send)
    {
        return find_value(1, 0, TSIZE/2-1, sbegin, send);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    static xor_tree tree;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a;
        cin >> a;
        tree.set_value(TSIZE/2+i, a);
    }
    for(uint32_t qi = 0; qi < q; qi++)
    {
        string com;
        cin >> com;
        uint32_t i, j;
        cin >> i >> j; i--; j--;
        if(com == "czytaj")
            cout << tree.find_value(i, j) << '\n';
        else if(com == "zamien")
        {
            uint32_t a = tree.values[TSIZE/2+i], b = tree.values[TSIZE/2+j];
            tree.set_value(TSIZE/2+j, a);
            tree.set_value(TSIZE/2+i, b);
        }
    }
}
