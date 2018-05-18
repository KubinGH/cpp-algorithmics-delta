#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e5, TSIZE = 1 << 18, MAXB = 1e3;
const uint32_t TO_CLEAR = 1u << 31;

template<typename T, T(*F)(T, T), T NONE, size_t N, T SET_NONE,
        void(*P)(size_t, size_t, size_t, array<T, N>&, array<T, N>&)>
struct segment_tree_intervalop
{
    array<T, N> values, to_set;
    static_assert(__builtin_popcount(N) == 1 and N > 4, "N != 2**k");
    size_t offset() const { return N/2 - 1; }
    size_t parent(size_t i) const { return (i - 1) / 2; }
    size_t left(size_t i) const { return 2 * i + 1; }
    size_t right(size_t i) const { return 2 * i + 2; }
    segment_tree_intervalop()
    {
        fill(values.begin() + offset(), values.end(), NONE);
        for(size_t i = offset(); i --> 0;)
            values[i] = F(values[left(i)], values[right(i)]);
        fill(to_set.begin(), to_set.end(), SET_NONE);
    }
    void clear()
    {
        fill(values.begin(), values.end(), NONE);
        fill(to_set.begin(), to_set.end(), SET_NONE);
    }
    void pull(size_t i, size_t tbegin, size_t tend)
    {
        if(to_set[i] == SET_NONE)
            return;
        P(i, tbegin, tend, values, to_set);
        to_set[i] = SET_NONE;
    }
    void set(size_t i, size_t tbegin, size_t tend,
                       size_t sbegin, size_t send, T value)
    {
        pull(i, tbegin, tend);
        if(tend < sbegin or send < tbegin)
            return;
        else if(sbegin <= tbegin and tend <= send)
        {
            //to_set[i] = F(to_set[i], value);
            pull(i, tbegin, tend);
            if(value & TO_CLEAR)
                to_set[i] = TO_CLEAR;
            else
                to_set[i] += value;
            pull(i, tbegin, tend);
        }
        else
        {
            set(left(i),  tbegin, (tbegin+tend)/2, sbegin, send, value);
            set(right(i), (tbegin+tend)/2+1, tend, sbegin, send, value);
            values[i] = F(values[left(i)], values[right(i)]);
        }
    }
    void set(size_t sbegin, size_t send, T value)
        { return set(0, 0, N/2 - 1, sbegin, send, value); }
    T get(size_t i, size_t tbegin, size_t tend,
                    size_t sbegin, size_t send)
    {
        pull(i, tbegin, tend);
        if(tend < sbegin or send < tbegin)
            return NONE;
        else if(sbegin <= tbegin and tend <= send)
            return values[i];
        else
            return F(get(left(i),  tbegin, (tbegin+tend)/2, sbegin, send),
                     get(right(i), (tbegin+tend)/2+1, tend, sbegin, send));
    }
    T get(size_t sbegin, size_t send)
        { return get(0, 0, N/2 - 1, sbegin, send); }
};
void pull_add(size_t i, size_t tbegin, size_t tend,
              array<uint32_t, TSIZE>& values,
              array<uint32_t, TSIZE>& to_set)
{
    if(tbegin < tend)
    {
        if(to_set[i] & TO_CLEAR)
        {
            to_set[2*i+1] = TO_CLEAR;
            to_set[2*i+2] = TO_CLEAR;
            to_set[i] ^= TO_CLEAR;
        }
        to_set[2*i+1] += to_set[i];
        to_set[2*i+2] += to_set[i];
    }
    if(to_set[i] & TO_CLEAR)
        values[i] = 0, to_set[i] ^= TO_CLEAR;
    values[i] += to_set[i];
}
uint32_t max_u32(uint32_t a, uint32_t b) { return a>b ? a : b; }



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static pair<uint32_t, uint32_t> intervals[MAX];
    static pair<uint32_t, uint32_t> events[2*MAX];
    uint32_t time = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a, b;
        cin >> a >> b;
        intervals[i] = make_pair(a, b);
        events[2*i].first = a; events[2*i].second = i;
        events[2*i+1].first = b+1; events[2*i+1].second = i;
        time = max(b+1, time);
    }
    sort(events, events + 2*n);
    uint32_t ei = 0;
//////////////////
if(time < MAXB)
{
    static bitset<MAXB> c_active, active[MAXB];
    for(uint32_t t = 0; t <= time; t++)
    {
        while(ei < 2*n and events[ei].first <= t)
        {
            c_active[events[ei].second] = not c_active[events[ei].second];
            ei++;
        }
        active[t] = c_active;
    }
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t k;
        cin >> k;
        c_active.reset();
        for(uint32_t j = 0; j < k; j++)
        {
            uint32_t a;
            cin >> a;
            c_active |= active[a];
        }
        cout << c_active.count() << "\n";
    }
}
//////////////////
else
{
    static bitset<MAX> is_active;
    static set<uint32_t> active[MAX];
    for(uint32_t t = 1; t <= time; t++)
    {
        active[t] = active[t-1];
        while(ei < 2*n and events[ei].first <= t)
        {
            uint32_t i = events[ei].second;
            is_active[i] = not is_active[i];
            if(is_active[i])
                active[t].insert(i);
            else
                active[t].erase(i);
            ei++;
        }
    }
    static segment_tree_intervalop<uint32_t, max_u32, 0, TSIZE, 0, pull_add>
        tree;
    for(uint32_t mi = 0; mi < m; mi++)
    {
        uint32_t k;
        cin >> k;
        uint32_t r = 0;
        is_active.reset();
        tree.set(0, time, TO_CLEAR);
        for(uint32_t ki = 0; ki < k; ki++)
        {
            uint32_t a;
            cin >> a;
            r += active[a].size();
            r -= tree.get(a, a);
            for(uint32_t i : active[a])
            {
                if(not is_active[i])
                {
                    is_active[i] = true;
                    tree.set(intervals[i].first, intervals[i].second, 1);
                }
            }
        }
        cout << r << "\n";
        cout.flush();
    }
}
}
