#include <bits/stdc++.h>

using namespace std;

typedef pair<uint32_t, uint32_t> pair_u32;

const size_t MAX = 1e6, TSIZE = 1 << 21;
const uint64_t INF = 1llu << 61;

struct interval_tree
{
    array<uint64_t, TSIZE> values;
    void set_value(uint32_t i, uint64_t value)
    {
        i += TSIZE/2 - 1;
        values[i] = value;
        while(i > 0)
            i--, i /= 2, values[i] = min(values[2*i+1], values[2*i+2]);
    }
    uint64_t find_value(uint32_t i, uint32_t tbegin, uint32_t tend, uint32_t sbegin, uint32_t send)
    {
        if(send < tbegin or tend < sbegin)
            return INF;
        else if(sbegin <= tbegin and tend <= send)
            return values[i];
        else
            return min(find_value(2*i+1, tbegin, (tbegin+tend)/2, sbegin, send),
                       find_value(2*i+2, (tbegin+tend)/2+1, tend, sbegin, send));
    }
    uint64_t find_value(uint32_t sbegin, uint32_t send)
    {
        if(sbegin < send)
            return find_value(0, 0, TSIZE/2 - 1, sbegin, send);
        else
            return values[sbegin + TSIZE/2 - 1];
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static pair<uint32_t, uint32_t> ends[MAX];
    static uint64_t segment_cost[MAX];
    static pair<uint32_t, uint32_t> segment_points[MAX];
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t start, stop;
        cin >> start >> stop >> segment_cost[i];
        ends[i].first = stop; ends[i].second = i;
        segment_points[i].first = start;
        segment_points[i].second = stop;
    }
    static interval_tree cost_tree; // @ [0, x]
    cost_tree.values.fill(INF);
    cost_tree.set_value(0, 0);
    sort(ends, ends + m);
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t index = ends[i].second,
                 tbegin = segment_points[index].first,
                 tend = segment_points[index].second;
        uint64_t cost = segment_cost[index];
        uint64_t new_value = cost + cost_tree.find_value(tbegin, tend),
                 old_value = cost_tree.find_value(tend, tend);
        if(new_value < old_value)
            cost_tree.set_value(tend, new_value);
    }
    cout << cost_tree.find_value(n, n);
}
