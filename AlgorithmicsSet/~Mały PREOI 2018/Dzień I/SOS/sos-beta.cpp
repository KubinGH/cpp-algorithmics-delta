#include <bits/stdc++.h>

using namespace std;

struct vec2d
{
    int64_t x, y;
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
    { return (b - a) ^ (c - a); }

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
        cin >> vertices[i].x >> vertices[i].y;
    auto find_visible = [&](uint32_t p) {
        uint32_t tan1 = -1u, tan2 = -1u;
        for(uint32_t i = 0, i0 = m - 1, i1 = 1; i < m; i++, i0++, i1++)
        {
            if(i0 == m) i0 = 0; if(i1 == m) i1 = 0;
            int64_t o1 = ori(points[p], vertices[i0], vertices[i]),
                    o2 = ori(points[p], vertices[i1], vertices[i]);
            if(sgn(o1) == sgn(o2) or o1 == 0 or o2 == 0)
            {
                if(tan1 != -1u and ori(points[p], vertices[tan1], vertices[i]) == 0
                   and +(vertices[i]-points[p]) > +(vertices[tan1]-points[p]))
                   tan1 = i;
                else if(tan2 != -1u and ori(points[p], vertices[tan2], vertices[i]) == 0
                        and +(vertices[i]-points[p]) > +(vertices[tan2]-points[p]))
                    tan2 = i;
                else if(tan1 != -1u)
                    tan2 = i;
                else
                    tan1 = i;
            }
        }
        if(ori(points[p], vertices[tan1], vertices[tan2]) < 0)
            swap(tan1, tan2);
        vector<uint32_t> V;
        cout << p+1 << " -> " << endl;
        cout << "tan " << tan1 << " " << tan2 << endl;
        for(uint32_t i = 0; i < n; i++) if(i != p)
        {
            cout << i+1 << ": " << (sgn(ori(points[p], points[i], vertices[tan1]))
              == sgn(ori(points[p], points[i], vertices[tan2]))) << " " << (sgn((points[p] - points[i]) * (points[p] - vertices[tan1])) >= 0) << endl;
            if(sgn(ori(points[p], points[i], vertices[tan1]))
              == sgn(ori(points[p], points[i], vertices[tan2]))
            or sgn((points[p] - points[i]) * (points[p] - vertices[tan1])) >= 0)
                V.push_back(i);
        }
        return V;
    };
    bitset<1<<20> in_result;
    auto V = find_visible(0);
    for(uint32_t v : V)
    {
        in_result[v] = true;
        for(uint32_t u : find_visible(v))
            in_result[u] = true;
    }
    in_result[0] = false;
    cout << in_result.count();
}
