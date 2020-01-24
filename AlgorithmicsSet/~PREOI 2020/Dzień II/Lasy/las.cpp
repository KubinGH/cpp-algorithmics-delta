#include <bits/stdc++.h>

using namespace std;

struct rect
{
    int x1, y1, x2, y2;

    int64_t area() const
    {
        return (int64_t) (x2 - x1) * (y2 - y1);
    }

    rect extend(int r) const
    {
        return {x1 - r, y1 - r, x2 + r, y2 + r};
    }

    friend rect operator& (const rect& a, const rect& b)
    {
        return {
            max(a.x1, b.x1), max(a.y1, b.y1),
            min(a.x2, b.x2), min(a.y2, b.y2)
        };
    }
};

istream& operator>> (istream& in, rect& q)
{
    return in >> q.x1 >> q.y1 >> q.x2 >> q.y2;
}

struct cover_tree
{
    size_t w;
    vector<pair<int, size_t>> values;
    vector<int> mutate;

    cover_tree(size_t n) : w(1 << __lg(2*n - 1)), values(2*w), mutate(2*w)
    {
        for(size_t i = w; i < 2*w; i++)
            values[i] = {0, 1};
        for(size_t i = w; i --> 1; )
            values[i] = F(values[2*i], values[2*i+1]);
    }

    pair<int, size_t> F(const pair<int, size_t>& a, const pair<int, size_t>& b)
    {
             if(a.first < b.first) return a;
        else if(a.first > b.first) return b;
        else return {a.first, a.second + b.second};
    }

    void pull(size_t i, size_t nodeL, size_t nodeR)
    {
        values[i].first += mutate[i];
        if(nodeL < nodeR)
        {
            mutate[2*i  ] += mutate[i];
            mutate[2*i+1] += mutate[i];
        }
        mutate[i] = 0;
    }

    void mut(size_t i, size_t nodeL, size_t nodeR, size_t getL, size_t getR, int value)
    {
        pull(i, nodeL, nodeR);
        if(nodeR < getL or getR < nodeL)
            {}
        else if(getL <= nodeL and nodeR <= getR)
            mutate[i] += value, pull(i, nodeL, nodeR);
        else
        {
            auto mid = (nodeL + nodeR) / 2;
            mut(2*i, nodeL, mid, getL, getR, value);
            mut(2*i+1, mid+1, nodeR, getL, getR, value);
            values[i] = F(values[2*i], values[2*i+1]);
        }
    }

    void mut(size_t L, size_t R, int v)
    {
        return mut(1, 0, w - 1, L, R, v);
    }

    size_t cover() const
    {
        return w - (values[1].first ? 0 : values[1].second);
    }
};


struct op { int x; int y1, y2; int v; };
bool operator< (const op& lhs, const op& rhs)
{
    return lhs.x < rhs.x;
}

int64_t rect_union_area(const vector<rect>& rects, rect scan)
{
    vector<op> Q;
    for(auto& r : rects)
      if(r.y1 < r.y2)
    {
        Q.push_back({r.x1, r.y1, r.y2 - 1, +1});
        Q.push_back({r.x2, r.y1, r.y2 - 1, -1});
    }
    sort(Q.begin(), Q.end());

    cover_tree T(scan.y2);
    int64_t result = 0;

    size_t i = 0;
    for(int x = scan.x1; x < scan.x2; x++)
    {
        while(i < Q.size() and x >= Q[i].x)
            T.mut(Q[i].y1, Q[i].y2, Q[i].v), i++;
        result += T.cover();
    }

    return result;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<rect> segments(n);
    for(auto& seg : segments)
        cin >> seg;

    int64_t p;
    cin >> p;

    rect scan;
    cin >> scan;

    int lo = 0, hi = max(scan.y2 - scan.y1, scan.x2 - scan.x1) + 1;
    while(lo < hi)
    {
        int mid = (lo + hi) / 2;
        vector<rect> rects(n);
        for(size_t i = 0; i < n; i++)
            rects[i] = segments[i].extend(mid) & scan;
        if(100 * rect_union_area(rects, scan) >= p * scan.area())
            hi = mid;
        else
            lo = mid+1;
    }

    cout << lo;
}
