#include <bits/stdc++.h>

using namespace std;

struct horsegment_t { uint32_t x1, x2, y; };

template<typename T>
typename multiset<T>::iterator
max_element(const multiset<T>& S) { return --S.end(); }
template<typename T>
typename multiset<T>::iterator
min_element(const multiset<T>& S) { return S.begin(); }

template<bool MinOrMax = 0>
uint32_t area_under_union(const vector<horsegment_t>& segments)
{
    vector<tuple<uint32_t, bool, uint32_t>> events;
    events.reserve(segments.size() * 2);
    for(auto s : segments)
    {
        events.emplace_back(s.x1, 0, s.y);
        events.emplace_back(s.x2, 1, s.y);
    }
    sort(events.begin(), events.end());
    uint32_t r = 0, lx = get<0>(events[0]);
    multiset<uint32_t> Y;
    for(auto e : events)
    {
        bool t; uint32_t x, y; tie(x, t, y) = e;
        if(not Y.empty())
        {
            uint32_t my = MinOrMax ? *max_element(Y) : *min_element(Y);
            r += (x - lx) * my;
        }
        if(t == 0)
            Y.insert(y);
        else
            Y.erase(y);
        lx = x;
    }
    return r;
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<horsegment_t> top_segments, bottom_segments;
    top_segments.reserve(n);
    bottom_segments.reserve(n);
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        top_segments.push_back({x1, x2, y2});
        bottom_segments.push_back({x1, x2, y1});
    }
    cout << area_under_union<1>(top_segments) - area_under_union<0>(bottom_segments);
}
