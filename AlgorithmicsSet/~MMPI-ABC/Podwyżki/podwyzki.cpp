#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;
const size_t TSIZE = 1 << 21;

struct interval_tree
{
    array<uint32_t, TSIZE> values, to_add;
    void push_down(uint32_t i, uint32_t tbegin, uint32_t tend)
    {
        if(to_add[i] == 0) return;
        values[i] += to_add[i];
        if(tbegin != tend)
        {
            to_add[2*i+1] += to_add[i];
            to_add[2*i+2] += to_add[i];
        }
        to_add[i] = 0;
    }
    void inc_interval(uint32_t i, uint32_t tbegin, uint32_t tend, uint32_t sbegin, uint32_t send)
    {
        if(tend < sbegin or send < tbegin)
            return;
        if(sbegin <= tbegin and tend <= send)
        {
            to_add[i]++;
            push_down(i, tbegin, tend);
        }
        else
        {
            push_down(i, tbegin, tend);
            inc_interval(2*i+1, tbegin, (tbegin+tend)/2, sbegin, send);
            inc_interval(2*i+2, (tbegin+tend)/2+1, tend, sbegin, send);
            values[i] = values[2*i+1] + to_add[2*i+1] + values[2*i+2] + to_add[2*i+2];
        }
    }
    void inc_interval(uint32_t sbegin, uint32_t send)
    {
        if(sbegin > send) return;
        inc_interval(0, 0, TSIZE/2-1, sbegin, send);
    }
    uint32_t find_value(uint32_t i, uint32_t tbegin, uint32_t tend, uint32_t sbegin, uint32_t send)
    {
        if(tend < sbegin or send < tbegin)
            return 0;
        push_down(i, tbegin, tend);
        if(sbegin <= tbegin and tend <= send)
            return values[i];
        else
            return find_value(2*i+1, tbegin, (tbegin+tend)/2, sbegin, send) +
                   find_value(2*i+2, (tbegin+tend)/2+1, tend, sbegin, send);
    }
    uint32_t find_value(uint32_t sbegin, uint32_t send)
    {
        if(sbegin > send) return 0;
        return find_value(0, 0, TSIZE/2-1, sbegin, send);
    }
    uint32_t find_value(uint32_t index)
    {
        return find_value(index, index);
    }
    uint32_t find_lower_bound(uint32_t value)
    {
        uint32_t lo = 1, hi = TSIZE/2-1;
        while(lo < hi)
        {
            uint32_t mid = (lo + hi + 1) / 2;
            if(find_value(mid) <= value)
                lo = mid;
            else
                hi = mid - 1;
        }
        return lo;
    }
    void iota()
    {
        for(uint32_t i = TSIZE/2; i < TSIZE; i++)
            values[i] = i - TSIZE/2 + 1;
        for(uint32_t i = TSIZE/2; i --> 0;)
            values[i] = values[2*i+1] + values[2*i+2];
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    static interval_tree tree;
    tree.iota();
    uint32_t n, m;
    cin >> n >> m;
    static array<uint32_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t x;
        cin >> x;
        tree.inc_interval(1, tree.find_lower_bound(x));
    }
    for(uint32_t i = 0; i < n; i++)
        cout << tree.find_value(A[i]) << ' ';
}
