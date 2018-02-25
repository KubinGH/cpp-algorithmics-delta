#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000000;
const size_t TSIZE = (1 << 26) - 1024;

struct interval_tree
{
    array<int32_t, TSIZE> values;
    array<bool, TSIZE> to_toggle;
    int32_t push_down(uint32_t i, uint32_t tbegin, uint32_t tend)
    {
        if(not to_toggle[i])
            return 0;
        int32_t len = (tend - tbegin + 1);
        if(len > 1)
        {
            to_toggle[2*i+1] = not to_toggle[2*i+1];
            to_toggle[2*i+2] = not to_toggle[2*i+2];
        }
        values[i] = len - values[i];
        to_toggle[i] = false;
        return 2*values[i] - len;
    }
    void toggle_interval(uint32_t i, uint32_t tbegin, uint32_t tend, uint32_t sbegin, uint32_t send)
    {
        push_down(i, tbegin, tend);
        if(tend < sbegin or send < tbegin)
            return;
        else if(sbegin <= tbegin and tend <= send)
        {
            to_toggle[i] = not to_toggle[i];
            push_down(i, tbegin, tend);
        }
        else
        {
            toggle_interval(2*i+1, tbegin, (tbegin+tend)/2, sbegin, send);
            toggle_interval(2*i+2, (tbegin+tend)/2+1, tend, sbegin, send);
            values[i] = values[2*i+1] + values[2*i+2];
        }
    }
    void toggle_interval(uint32_t sbegin, uint32_t send)
    {
        toggle_interval(0, 0, TSIZE/2-1, sbegin, send);
    }
    int32_t find_value(uint32_t i, uint32_t tbegin, uint32_t tend, uint32_t sbegin, uint32_t send)
    {
        push_down(i, tbegin, tend);
        if(tend < sbegin or send < tbegin)
            return 0;
        if(sbegin <= tbegin and tend <= send)
            return values[i];
        else
            return find_value(2*i+1, tbegin, (tbegin+tend)/2, sbegin, send) +
                   find_value(2*i+2, (tbegin+tend)/2+1, tend, sbegin, send);
    }
    int32_t find_value(uint32_t sbegin, uint32_t send)
    {
        return find_value(0, 0, TSIZE/2-1, sbegin, send);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static interval_tree tree;
    tree.toggle_interval(0, n-1);
    for(uint32_t i = 0; i < m; i++)
    {
        char c; uint32_t a, b;
        cin >> c >> a >> b; a--; b--;
        if(c == '?')
            cout << tree.find_value(a, b) << '\n';
        else if(c == '*')
            tree.toggle_interval(a, b);
    }
}
