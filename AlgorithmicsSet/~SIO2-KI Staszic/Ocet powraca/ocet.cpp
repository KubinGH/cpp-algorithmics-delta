
#include <bits/stdc++.h>

using namespace std;

struct event_t
{
    uint64_t t, a, b;
};
enum event_types
{
    COUNT_INTERVAL = 0, ADD_VALUE = 1, SUB_VALUE = 2, NO = 3, ZERO = 4
};


const uint64_t MAX = 500010;
const uint64_t TSIZE = 1 << 20;

struct interval_tree
{
    array<uint64_t, TSIZE> values;
    void add_value(uint64_t node, uint64_t value)
    {
        values[node] += value;
        while(node != 1)
            node/=2, values[node] += value;
    }
    void sub_value(uint64_t node, uint64_t value)
    {
        values[node] -= value;
        while(node != 1)
            node/=2, values[node] -= value;
    }
    uint64_t find_sum(uint64_t node, uint64_t tbegin, uint64_t tend, uint64_t sbegin, uint64_t send)
    {
        if(send < tbegin or tend < sbegin)
            return 0;
        else if(sbegin <= tbegin and tend <= send)
            return values[node];
        else
        {
            uint64_t left = find_sum(node*2, tbegin, (tbegin+tend)/2, sbegin, send);
            uint64_t right = find_sum(node*2+1, (tbegin+tend)/2+1, tend, sbegin, send);
            return left + right;
        }
    }
    uint64_t find_sum(uint64_t sbegin, uint64_t send)
    {
        return find_sum(1, 0, TSIZE/2-1, sbegin, send);
    }
};


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t n;
    cin >> n;
    static array<event_t, MAX> events;
    static array<uint64_t, MAX> values;
    uint64_t vi = 0;
    for(uint64_t i = 0; i < n; i++)
    {
        cin >> events[i].t >> events[i].a >> events[i].b;
        if(events[i].t == 1)
            values[vi++] = events[i].b;
    }
    uint64_t vn = vi+1;
    sort(values.begin(), values.begin() + vn);
    for(uint64_t i = 0; i < n; i++)
    {
        switch(events[i].t)
        {
            case event_types::COUNT_INTERVAL:
                if(events[i].a > values[vi])
                    events[i].t = event_types::ZERO;
                else
                {
                    if(events[i].a < values[0])
                        events[i].a = 0;
                    else
                        events[i].a = lower_bound(values.begin(), values.begin() + vn,
                                                  events[i].a) - values.begin();
                    if(events[i].b > values[vi])
                        events[i].b = vi;
                    else if(events[i].b < values[0])
                        events[i].t = event_types::ZERO;
                    else
                        events[i].b = upper_bound(values.begin(), values.begin() + vn,
                                                  events[i].b) - values.begin() - 1;
                }
                break;
            case event_types::ADD_VALUE:
                events[i].b = lower_bound(values.begin(), values.begin() + vn, events[i].b)
                              - values.begin();
                break;
            case event_types::SUB_VALUE:
                uint64_t* it = lower_bound(values.begin(), values.begin() + vn, events[i].b);
                if(*it == events[i].b)
                    events[i].b = it - values.begin();
                else
                    events[i].t = event_types::NO;
                break;
        }
    }
    static interval_tree tree;
    for(uint64_t i = 0; i < n; i++)
    {
        if(events[i].t == event_types::COUNT_INTERVAL)
            cout << tree.find_sum(events[i].a, events[i].b) << '\n';
        else if(events[i].t == event_types::ADD_VALUE)
            tree.add_value(TSIZE/2+events[i].b, events[i].a);
        else if(events[i].t == event_types::SUB_VALUE)
        {
            if(tree.values[TSIZE/2+events[i].b] >= events[i].a)
            {
                cout << "OK\n";
                tree.sub_value(TSIZE/2+events[i].b, events[i].a);
            }
            else
                cout << "NIE\n";
        }
        else if(events[i].t == event_types::NO)
            cout << "NIE\n";
        else if(events[i].t == event_types::ZERO)
            cout << "0\n";
    }
}
