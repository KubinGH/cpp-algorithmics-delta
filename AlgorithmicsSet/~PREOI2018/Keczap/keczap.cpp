#include <bits/stdc++.h>

using namespace std;

typedef array<uint32_t, 4> dt;

const size_t MAX = 10000;
const size_t TSIZE = 1 << 18;

inline void addo(const dt& a, const dt& b, dt& out)
{
    out[0] = a[0] + b[0]; out[1] = a[1] + b[1];
    out[2] = a[2] + b[2]; out[3] = a[3] + b[3];
}

struct interval_tree
{
    array<dt, TSIZE> values;
    array<uint32_t, TSIZE> leaf_values;
    interval_tree()
    {
        for(uint32_t i = 0; i < TSIZE; i++)
        {
            for(uint32_t j = 0; j < 4; j++)
                values[i][j] = 0;
            leaf_values[i] = 0;
        }
        for(uint32_t i = 0; i < TSIZE/2; i++)
            add_value(i, 0);
    }
    void add_value(uint32_t i, uint32_t value)
    {
        i += TSIZE/2;
        leaf_values[i] += value;
        values[i][0] = (leaf_values[i] % 2) == 0; values[i][1] = (leaf_values[i] % 3) == 0;
        values[i][2] = (leaf_values[i] % 4) == 0; values[i][3] = (leaf_values[i] % 5) == 0;
        while(i != 1)
            i /= 2, addo(values[2*i], values[2*i+1], values[i]);
    }
    uint32_t find_value(uint32_t i, uint32_t tbegin, uint32_t tend, uint32_t sbegin, uint32_t send, uint32_t k)
    {
        if(send < tbegin or tend < sbegin)
            return 0;
        else if(sbegin <= tbegin and tend <= send)
            return values[i][k-2];
        else
            return find_value(2*i, tbegin, (tbegin+tend)/2, sbegin, send, k) +
                   find_value(2*i+1, (tbegin+tend)/2+1, tend, sbegin, send, k);
    }
    uint32_t find_value(uint32_t sbegin, uint32_t send, uint32_t k)
    {
        if(k == 1)
            return send - sbegin + 1;
        else
            return find_value(1, 0, TSIZE/2-1, sbegin, send, k);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    static interval_tree tree;
    for(uint32_t qi = 0; qi < q; qi++)
    {
        string command;
        cin >> command;
        uint32_t i, j, k;
        if(command == "WINCYJ")
        {
            cin >> i >> k; i--;
            tree.add_value(i, k);
        }
        else if(command == "KECZAP")
        {
            cin >> i >> j >> k; i--; j--;
            cout << tree.find_value(i, j, k) << '\n';
        }
    }
}
