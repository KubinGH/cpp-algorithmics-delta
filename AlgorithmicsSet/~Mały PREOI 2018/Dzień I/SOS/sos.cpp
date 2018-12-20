#include <bits/stdc++.h>

using namespace std;

struct vec2d
{
    int64_t x, y; bool flag;
    vec2d() : x(0), y(0), flag(false) {}
    vec2d(int64_t _x, int64_t _y, bool _flag = false)
        : x(_x), y(_y), flag(_flag) {}
};
vec2d operator+ (vec2d a, vec2d b) { return {a.x+b.x, a.y+b.y}; }
vec2d operator- (vec2d a) { return {-a.x, -a.y}; }
vec2d operator- (vec2d a, vec2d b) { return a + (-b); }
int64_t operator* (vec2d a, vec2d b) { return a.x*b.x + a.y*b.y; }
int64_t operator^ (vec2d a, vec2d b) { return a.x*b.y - a.y*b.x; }
int64_t operator+ (vec2d a) { return a.x*a.x + a.y*a.y; }
template<typename T>
int sgn(T x) { return int(x > 0) - int(x < 0); }
int64_t ori(const vec2d& a, const vec2d& b, const vec2d& c)
    { return (c.y-a.y) * (b.x-a.x) - (b.y-a.y) * (c.x-a.x); }

bool ons(const vec2d& a, const vec2d& b, const vec2d& p)
{
    return (b.x <= max(a.x, p.x) and b.x >= min(a.x, p.x) and
            b.y <= max(a.y, p.y) and b.y >= min(a.y, p.y));
}
bool intersects(const vec2d& a, const vec2d& b, const vec2d& c, const vec2d& d)
{
    int64_t o1 = ori(a, b, c), o2 = ori(a, b, d),
            o3 = ori(c, d, a), o4 = ori(c, d, b);
    if((o1 == 0 and ons(a, c, b)) or
       (o2 == 0 and ons(a, d, b)) or
       (o3 == 0 and ons(c, a, d)) or
       (o4 == 0 and ons(c, b, d)))
        return false;
    else if(sgn(o1) != sgn(o2) and sgn(o3) != sgn(o4))
        return true;
    else
        return false;
}
struct angle_cmp
{
    vec2d s;
    bool operator() (const vec2d& a, const vec2d& b)
    {
        auto v = (a - s) ^ (b - s);
        if(v == 0)
            return +(a - s) < +(b - s);
        else
            return a.flag < b.flag or (a.flag == b.flag and v > 0);
    }
};

void angle_sort(vector<vec2d>& points, vec2d s)
{
    size_t n = points.size();
    vector<vec2d> upper, lower;
    upper.reserve(n); lower.reserve(n);
    for(auto p : points)
        if(p.y >= s.y)
            upper.push_back(p);
        else
            lower.push_back(p);
    sort(upper.begin(), upper.end(), angle_cmp{s});
    sort(lower.begin(), lower.end(), angle_cmp{s});
    points.clear();
    for(auto p : upper)
        points.push_back(p);
    for(auto p : lower)
        points.push_back(p);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<vec2d> points(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> points[i].x >> points[i].y;
    uint32_t m;
    cin >> m;
    vector<vec2d> vertices(m);
    for(uint32_t i = 0; i < m; i++)
        cin >> vertices[i].x >> vertices[i].y, vertices[i].flag = true;

    auto get_visible = [&](uint32_t p) {
        /*
        vector<uint32_t> V;
        for(uint32_t i = 0; i < n; i++) if(i != p)
        {
            bool ok = true;
            for(uint32_t j = 0; j < m and ok; j++)
                if(intersects(points[p], points[i], vertices[j], vertices[(j+1)%m]))
                    ok = false;
            if(ok)
                V.push_back(i);
        }
        return V;
        */
        vector<uint32_t> W(vertices.begin(), vertices.end());
        angle_sort(W, points[p]);
        auto a = W.front(), b = W.back();
        bool invert = intersects(a, b, points[p], W[1]);
        vector<uint32_t> Q;
        for(uint32_t i = 0; i < n; i++) if(i != p)
            Q.push_back(points[i]);
        vector<uint32_t> V; bool collect = false;
        angle_sort(Q, points[p]);
        for(uint32_t i = 0; i < n; i++)
        {
            if(sgn())
        }

    };

    auto initial = get_visible(0);
    bitset<1<<20> in_result;
    set<uint32_t> result(initial.begin(), initial.end());
    for(uint32_t i : initial)
    {
        in_result[i] = true;
        for(uint32_t j : get_visible(i))
            in_result[j] = true;
    }
    in_result[0] = false;
    cout << in_result.count();
}
