#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e6, TSIZE = 1 << 23, MAX_C = 1e6;

typedef pair<int32_t, int32_t> pair_i32;

struct point
{
    int32_t x, y;
    point() : x(0), y(0) {}
    point(int32_t _x, int32_t _y) : x(_x), y(_y) {}
    operator< (const point& o) const
    {
        if(x != o.x)
            return x < o.x;
        else
            return y < o.y;
    }
};

istream& operator>> (istream& in, point& o) { return in >> o.x >> o.y; }

struct event_t
{
    uint32_t type; point epoint;
    event_t() : type(0), epoint(0, 0) {}
    event_t(uint32_t _t, point _p) : type(_t), epoint(_p) {}
    operator< (const event_t& o) const
    {
        if(epoint.x != o.epoint.x)
            return epoint.x < o.epoint.x;
        else if(type != o.type)
            return type < o.type;
        else
            return epoint.y < o.epoint.y;
    }
};

struct segment_tree
{
    array<uint32_t, TSIZE> values;
    void increment(int32_t i)
    {
        i += TSIZE/2;
        values[i]++;
        while(i > 1)
            i/=2, values[i]++;
    }
    void decrement(int32_t i)
    {
        i += TSIZE/2;
        values[i]--;
        while(i > 1)
            i/=2, values[i]--;
    }
    uint32_t get(uint32_t i, uint32_t tbegin, uint32_t tend,
                 uint32_t sbegin, uint32_t send)
    {
        if(send < tbegin or tend < sbegin)
            return 0;
        else if(sbegin <= tbegin and tend <= send)
            return values[i];
        else
            return get(2*i,   tbegin, (tbegin+tend)/2, sbegin, send) +
                   get(2*i+1, (tbegin+tend)/2+1, tend, sbegin, send);
    }
    uint32_t get(int32_t sbegin, int32_t send)
    {
        return get(1, 0, TSIZE/2-1, sbegin, send);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    vector<point> vertices(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> vertices[i], vertices[i].x += MAX_C, vertices[i].y += MAX_C;
    vector<event_t> events;
    for(uint32_t i = 0; i < n; i++)
    {
        point p1 = vertices[i], p2 = vertices[(i+1)%n];
        if(p1.y == p2.y)
        {
            if(p1.x > p2.x) swap(p1, p2);
            events.emplace_back(1, p2);
            events.emplace_back(0, p1);
        }
    }
    for(uint32_t i = 0; i < m; i++)
    {
        point p;
        cin >> p;
        p.x += MAX_C; p.y += MAX_C;
        events.emplace_back(i+2, p);
    }
    sort(events.begin(), events.end());
    static segment_tree active_vertices;
    vector<bool> result(m);
    for(event_t event : events)
    {
        uint32_t t = event.type; point p = event.epoint;
        //cout << (int)t << ": " << p.x-(int)MAX_C << " " << p.y-(int)MAX_C << endl;
        if(t == 0)
            active_vertices.increment(p.y);
        else if(t == 1)
            active_vertices.decrement(p.y);
        else
        {
            result[t-2] = active_vertices.get(p.y, 2*MAX_C)%2 or
                          active_vertices.get(p.y, p.y) == 1;
        }
    }
    for(bool r : result)
        cout << (r ? "T" : "N");
}

