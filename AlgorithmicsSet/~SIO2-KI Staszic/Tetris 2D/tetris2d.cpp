#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;
const size_t MAX_TSIZE = 1 << 21;

uint32_t clz(uint32_t n)
{
    return __builtin_clz(n);
}

struct interval_tree
{
    size_t tsize;
    array<uint32_t, MAX_TSIZE> values, to_set;
    interval_tree(uint32_t n)
    {
        if(n == 1) n++;
        tsize = 1 << (31 - clz(n) + (__builtin_popcount(n) == 1 ? 1 : 2));
        to_set.fill(-1u);
    }
    void push_down(uint32_t i, uint32_t tbegin, uint32_t tend, uint32_t value = -1)
    {
        if(value != -1u)
            to_set[i] = value;
        if(to_set[i] != -1u)
        {
            values[i] = to_set[i];
            if(tbegin != tend)
            {
                to_set[2*i+1] = to_set[i];
                to_set[2*i+2] = to_set[i];
            }
            to_set[i] = -1u;
        }
    }
    void set_value(uint32_t i, uint32_t tbegin, uint32_t tend, uint32_t sbegin, uint32_t send, uint32_t value)
    {
        //cerr << "set_value " << i << " " << tbegin << " " << tend << " " << sbegin << " " << send << endl;
        if(tend < sbegin or send < tbegin)
            return;
        else if(sbegin <= tbegin and tend <= send)
            push_down(i, tbegin, tend, value);
        else
        {
            set_value(2*i+1, tbegin, (tbegin+tend)/2, sbegin, send, value);
            set_value(2*i+2, (tbegin+tend)/2+1, tend, sbegin, send, value);
            values[i] = max(values[2*i+1], values[2*i+2]);
        }
    }
    void set_value(uint32_t sbegin, uint32_t send, uint32_t value)
    {
        set_value(0, 0, tsize/2-1, sbegin, send, value);
    }
    uint32_t find_value(uint32_t i, uint32_t tbegin, uint32_t tend, uint32_t sbegin, uint32_t send)
    {
        //cerr << "find_value " << i << " " << tbegin << " " << tend << " " << sbegin << " " << send << endl;
        if(tend < sbegin or send < tbegin)
            return 0;
        push_down(i, tbegin, tend);
        if(sbegin <= tbegin and tend <= send)
            return values[i];
        else
            return max(find_value(2*i+1, tbegin, (tbegin+tend)/2, sbegin, send),
                       find_value(2*i+2, (tbegin+tend)/2+1, tend, sbegin, send));
    }
    uint32_t find_value(uint32_t sbegin, uint32_t send)
    {
        return find_value(0, 0, tsize/2-1, sbegin, send);
    }
    uint32_t find_value()
    {
        return find_value(0, tsize/2-1);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t w, n;
    cin >> w >> n;
    static interval_tree tree(w);
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t l, x;
        cin >> l >> x;
        uint32_t v = tree.find_value(x, x+l-1);
        //cerr << "set " << v << " @ " << x << ".." << x + l - 1 << endl;
        tree.set_value(x, x + l - 1, v + 1);
    }
    cout << tree.find_value();
}
