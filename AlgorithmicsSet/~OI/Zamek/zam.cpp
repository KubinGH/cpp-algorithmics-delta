#include <bits/stdc++.h>

using namespace std;

struct point_t { uint32_t x, y; };
istream& operator>> (istream& in, point_t& r)
    { return in >> r.x >> r.y; }

struct segment_t { uint32_t a, b, i; };

struct rect_t
{
    uint32_t x1, y1, x2, y2, i;
    bool contains(const point_t& p)
    {
        return x1 <= p.x and p.x <= x2 and
               y1 <= p.y and p.y <= y2;
    }
};
istream& operator>> (istream& in, rect_t& r)
    { return in >> r.x1 >> r.y1 >> r.x2 >> r.y2; }

template<typename Callable>
void segment_overlaps(uint32_t d, vector<segment_t>& segs,
                      const vector<vector<uint32_t>>& runs,
                      Callable action)
{
    map<uint32_t, uint32_t> owner;
    segs.push_back({0, d, owner[d] = segs.size()});
    for(const auto& run : runs)
    {
        vector<uint32_t> to_erase;
        for(uint32_t i : run)
        {
            auto curr = segs[i];
            uint32_t j;
            for(auto it = owner.upper_bound(curr.a);
                it != owner.end() and segs[j = it->second].a < curr.b; ++it)
            {
                auto prev = segs[j];
                // prev.b > curr.a and prev.a < curr.b
                if(prev.i != segs.size() - 1)
                    action(curr, prev);
                to_erase.push_back(prev.b);
            }
        }

        for(auto b : to_erase)
            owner.erase(b);
        for(uint32_t i : run)
        {
            auto curr = segs[i];
            if(curr.a < curr.b)
                owner[curr.b] = i;
        }
    }
    segs.pop_back();
}

pair<vector<segment_t>, vector<vector<uint32_t>>>
begin_verticals(const vector<rect_t>& rects)
{
    const uint32_t n = rects.size();
    using tri_u32 = tuple<uint32_t, uint32_t, uint32_t>;
    vector<tri_u32> events(n);
    vector<segment_t> segs(n);
    for(uint32_t i = 0; i < n; i++)
    {
        segs[i] = {rects[i].y1, rects[i].y2, i};
        events[i] = tri_u32{rects[i].x1, rects[i].y1, i};
    }
    sort(events.begin(), events.end());
    vector<vector<uint32_t>> runs;
    for(uint32_t j = 0; j < n; j++)
    {
        uint32_t i = get<2>(events[j]);
        if(runs.empty() or rects[runs.back().back()].x1 != rects[i].x1)
            runs.emplace_back();
        runs.back().push_back(i);
    }
    return {segs, runs};
}

void vertical_sweep(uint32_t w, uint32_t h, const vector<rect_t>& rects,
                    vector<vector<uint32_t>>& conn)
{
    (void)w;
    auto z = begin_verticals(rects);
    auto segs = z.first; auto runs = z.second;
    segment_overlaps(h, segs, runs, [&](segment_t curr, segment_t prev) {
        conn[curr.i].push_back(prev.i);
        conn[prev.i].push_back(curr.i);
    });
}

void horizontal_sweep(uint32_t w, uint32_t h, vector<rect_t>& rects,
                      vector<vector<uint32_t>>& conn)
{
    auto transpose_rects = [&]() {
        for(uint32_t i = 0; i < rects.size(); i++)
            swap(rects[i].x1, rects[i].y1), swap(rects[i].x2, rects[i].y2);
    };
    transpose_rects();
    vertical_sweep(h, w, rects, conn);
    transpose_rects();
}

void mark_containers(uint32_t w, uint32_t h, vector<rect_t>& rects,
                     const vector<point_t>& points, vector<bool>& lock)
{
    (void)w;
    for(auto p : points)
        rects.push_back({p.x, p.y, p.x, p.y, rects.size()});
    auto z = begin_verticals(rects);
    auto segs = z.first; auto runs = z.second;
    segment_overlaps(h, segs, runs, [&](segment_t curr, segment_t prev) {
        if(curr.a == curr.b)
            lock[prev.i] = true;
    });
    for(uint32_t i = 0; i < points.size(); i++)
        rects.pop_back();
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t w, h, n, m;
    cin >> w >> h >> n >> m;
    uint32_t startX, startY, targetX, targetY;
    cin >> startX >> startY >> targetX >> targetY;
    vector<rect_t> rects(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> rects[i], rects[i].i = i;
    vector<vector<uint32_t>> conn(n);
    vertical_sweep(w, h, rects, conn);
    horizontal_sweep(w, h, rects, conn);

    vector<point_t> points(m);
    for(uint32_t i = 0; i < m; i++)
        cin >> points[i];

    vector<bool> lock(n);
    mark_containers(w, h, rects, points, lock);

    uint32_t start = -1u, target = -1u;
    for(uint32_t i = 0; i < n; i++)
    {
        if(rects[i].contains({startX, startY}))
            start = i;
        if(rects[i].contains({targetX, targetY}))
            target = i;
    }

    vector<uint32_t> dist(n, -1u);
    queue<uint32_t> Q;
    lock[start] = true; dist[start] = 1; Q.push(start);
    while(not Q.empty())
    {
        uint32_t u = Q.front(); Q.pop();
        for(uint32_t v : conn[u])
            if(not lock[v])
                lock[v] = true, dist[v] = dist[u] + 1, Q.push(v);
    }
    cout << dist[target];
}
