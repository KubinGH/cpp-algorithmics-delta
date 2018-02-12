#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 5000;

typedef pair<uint32_t, uint32_t> pair_u32;

struct point_t
{
    int32_t x, y;
    point_t() : x(0), y(0) {}
    point_t(int32_t xi, int32_t yi)
    {
         x = xi; y = yi;
    }
    bool operator<(const point_t& o) const
    {
        return x < o.x or (not (o.x < x) and y < o.y);
    }
    bool operator>(const point_t& o) const
    {
        return x > o.x or (not (o.x > x) and y > o.y);
    }
    bool operator==(const point_t& o) const
    {
        return x == o.x and y == o.y;
    }
    bool operator!=(const point_t& o) const
    {
        return x != o.x or y != o.y;
    }
} START_A(-1e8, -1e7), START_B(1e8, -1e7), START_C(0, 1e9);


uint64_t find_sqrt_ge(uint64_t n)
{
    if(n == 0) return 0;
    else if(n == 1) return 1;
    else if(n == 2) return 2;
    else if(n == 3) return 2;
    else if(n == 4) return 2;
    uint64_t lo = 1, hi = n;
    while(lo < hi)
    {
        uint64_t x = (lo+hi) / 2;
        if(x*x >= n)
            hi = x;
        else
            lo = x + 1;
    }
    return lo;
}

uint32_t dist(const point_t& a, const point_t& b)
{
    uint64_t dx = abs(a.x - b.x), dy = abs(a.y - b.y);
    return find_sqrt_ge(dx*dx + dy*dy);
}

struct edge_t
{
    point_t first, second;
    edge_t() {}
    edge_t(point_t a, point_t b)
    {
        if(a > b)
            swap(a, b);
        first = a; second = b;
    }
    bool operator!=(const edge_t& o) const
    {
        return first != o.first or second != o.second;
    }
    bool operator==(const edge_t& o) const
    {
        return first == o.first and second == o.second;
    }
    bool operator<(const edge_t& o) const
    {
        return first < o.first or (not (o.first < first) and second < o.second);
    }
};

struct triangle_t
{
    point_t a, b, c;
    edge_t ab, bc, ac;
    triangle_t() {}
    triangle_t(point_t ai, point_t bi, point_t ci)
    {
        a = ai; b = bi; c = ci;
        if(b > c)
            swap(b, c);
        if(a > b)
            swap(a, b);
        if(b > c)
            swap(b, c);
        ab = edge_t(a, b); bc = edge_t(b, c); ac = edge_t(a, c);
    }
    bool circumcircle_contains(const point_t& p)
    {
        double ab = (a.x * a.x) + (a.y * a.y);
        double cd = (b.x * b.x) + (b.y * b.y);
        double ef = (c.x * c.x) + (c.y * c.y);

        double circum_x = (ab * (c.y - b.y) + cd * (a.y - c.y) + ef * (b.y - a.y)) / (a.x * (c.y - b.y) + b.x * (a.y - c.y) + c.x * (b.y - a.y)) / 2.f;
        double circum_y = (ab * (c.x - b.x) + cd * (a.x - c.x) + ef * (b.x - a.x)) / (a.y * (c.x - b.x) + b.y * (a.x - c.x) + c.y * (b.x - a.x)) / 2.f;
        double circum_radius = sqrt(((a.x - circum_x) * (a.x - circum_x)) + ((a.y - circum_y) * (a.y - circum_y)));

        double dist = sqrt(((p.x - circum_x) * (p.x - circum_x)) + ((p.y - circum_y) * (p.y - circum_y)));
        return dist <= circum_radius;
    }
    bool operator==(const triangle_t& o) const
    {
        return a == o.a and b == o.b and c == o.c;
    }
    bool operator!=(const triangle_t& o) const
    {
        return a != o.a or b != o.b or c != o.c;
    }
};

struct disjoint_set
{
    array<uint32_t, MAX> parent, nrank, ncount;
    disjoint_set()
    {
        iota(parent.begin(), parent.end(), 0);
        ncount.fill(1);
    }
    uint32_t find_root(uint32_t node)
    {
        if(parent[node] == node)
            return node;
        parent[node] = find_root(parent[node]);
        return parent[node];
    }
    void unite(uint32_t first_node, uint32_t second_node)
    {
        uint32_t first = find_root(first_node), second = find_root(second_node);
        if(nrank[second] > nrank[first])
        {
            parent[first] = second;
            ncount[second] += ncount[first];
        }
        else
        {
            if(nrank[first] == nrank[second])
                nrank[first]++;
            parent[second] = first;
            ncount[first] += ncount[second];
        }
    }
};

ostream& operator<< (ostream& out, const point_t& o)
{
    out << "(" << o.x << ", " << o.y << ")";
    return out;
}

ostream& operator<< (ostream& out, const edge_t& o)
{
    out << "edge_t(" << o.first << ", " << o.second << ")";
    return out;
}

ostream& operator<< (ostream& out, const triangle_t& o)
{
    out << "triangle_t(" << o.a << ", " << o.b << ", " << o.c << ")";
    return out;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<point_t, MAX> points;
    map<point_t, uint32_t> point_idx;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> points[i].x >> points[i].y;
        point_idx[points[i]] = i;
    }
    list<triangle_t> triangulation;
    triangulation.emplace_back(START_A, START_B, START_C);
    if(n > 2) for(uint32_t p = 0; p < n; p++)
    {
        //cerr << "point " << points[p] << endl;
        vector<edge_t> polygon;
        list<triangle_t> bad;
        for(auto it = triangulation.begin(); it != triangulation.end(); it++)
        {
            if(it->circumcircle_contains(points[p]))
            {
                //cerr << "bad " << *it << endl;
                polygon.push_back(it->ab);
                polygon.push_back(it->bc);
                polygon.push_back(it->ac);
                triangulation.erase(it++);
            }
        }
        sort(polygon.begin(), polygon.end());
        if(polygon.size() > 1) for(uint32_t i = 0; i < polygon.size(); i++)
        {
            if(i == 0 and polygon[0] != polygon[1])
            {
                triangulation.emplace_back(polygon[0].first, polygon[0].second, points[p]);
                //cerr << "push " << triangulation.back() << endl;
            }
            else if((i == polygon.size() - 1 and polygon[i - 1] != polygon[i]) or
                    (i > 0 and i < polygon.size() - 1 and polygon[i - 1] != polygon[i] and polygon[i] != polygon[i + 1]))
            {
                triangulation.emplace_back(polygon[i].first, polygon[i].second, points[p]);
                //cerr << "push " << triangulation.back() << endl;
            }
        }
        else if(polygon.size() == 1)
        {
            triangulation.emplace_back(polygon[0].first, polygon[0].second, points[p]);
            //cerr << "push " << triangulation.back() << endl;
        }
        polygon.clear();
    }
    priority_queue<pair<uint32_t, pair_u32>,
                   vector<pair<uint32_t, pair_u32> >,
                   greater<pair<uint32_t, pair_u32> > > edge_heap;
    if(n > 2) for(auto it = triangulation.begin(); it != triangulation.end(); it++)
    {
        point_t& a = it->a, b = it->b, c = it->c;
        if(a == START_A or a == START_B or a == START_C or
           b == START_A or b == START_B or b == START_C or
           c == START_A or c == START_B or c == START_C)
            {}
        else
        {
            //cerr << "result " << it->ab << " " << it->bc << " " << it->ac << endl;
            edge_heap.emplace(dist(a, b), make_pair(point_idx[a], point_idx[b]));
            edge_heap.emplace(dist(a, c), make_pair(point_idx[a], point_idx[c]));
            edge_heap.emplace(dist(b, c), make_pair(point_idx[b], point_idx[c]));
        }
    }
    else if(n == 2)
    {
        edge_heap.emplace(dist(points[0], points[1]), make_pair(0, 1));
    }
    static disjoint_set dset;
    dset.nrank[0] = n + 1;
    uint32_t maxim = 0;
    while(not edge_heap.empty() and dset.ncount[0] < n)
    {
        pair<uint32_t, pair_u32> e = edge_heap.top(); edge_heap.pop();
        uint32_t w = e.first, u = e.second.first, v = e.second.second;
        if(dset.find_root(u) != dset.find_root(v))
        {
            maxim = max(w, maxim);
            dset.unite(u, v);
        }
    }
    cout << static_cast<uint64_t>(n - 1) * maxim;
}
