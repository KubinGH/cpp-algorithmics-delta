#include <bits/stdc++.h>

using namespace std;


template<typename T>
using point_t = complex<T>;
#define X real()
#define Y imag()

template<typename T>
T ori(const point_t<T>& a, const point_t<T>& b, const point_t<T>& c)
{
    return (c.Y-a.Y) * (b.X-a.X) - (b.Y-a.Y) * (c.X-a.X);
}
template<typename T, bool INCLUDE_COLINEAR = true>
vector<point_t<T>> convex_hull(vector<point_t<T>>& points)
{
    sort(
         points.begin(), points.end(),
         [](const point_t<T>& lhs, const point_t<T>& rhs) {
            return lhs.X < rhs.X or (lhs.X == rhs.X and lhs.Y < rhs.Y);
    });
    vector<point_t<T>> hull; hull.reserve(points.size()+2);
    for(uint32_t phase = 0; phase < 2; phase++)
    {
        size_t start = hull.size();
        for(const point_t<T>& point : points)
        {
            while(
                hull.size() >= start + 2 and
                (INCLUDE_COLINEAR
                ? (ori(point, hull[hull.size()-1], hull[hull.size()-2]) <= 0)
                : (ori(point, hull[hull.size()-1], hull[hull.size()-2]) < 0))
            ) hull.pop_back();
            hull.push_back(point);
        }
        hull.pop_back();
        reverse(points.begin(), points.end());
    }
    if(hull.size() == 2 and hull[0] == hull[1]) hull.pop_back();
    return hull;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t t;
    cin >> t;
    cout << fixed << setprecision(2);
    while(t --> 0)
    {
        uint32_t n;
        cin >> n;
        vector<point_t<int32_t>> points; points.reserve(n);
        static unordered_map<int32_t, uint32_t> buckets[1<<15];
        for(uint32_t i = 0; i < (1<<15); i++)
            buckets[i].clear();
        for(uint32_t i = 0, f = 0; i < n; i++)
        {
            int32_t x, y;
            cin >> x >> y;
            if(buckets[(1<<14)+x].find(y) == buckets[(1<<14)+x].end())
            {
                buckets[(1<<14)+x][y] = i + f;
                points.emplace_back(x, y);
            }
            else
                i--, n--, f++;
        }
        vector<point_t<int32_t>> hull = convex_hull(points);
        if(hull.empty())
        {
            cout << "0.00\n1\n\n";
            continue;
        }
        reverse(hull.begin(), hull.end());
        double result = 0;
        uint32_t bottomleft_idx = 0;
        point_t<int32_t> bottomleft = hull[0];
        for(uint32_t i = 0; i < hull.size(); i++)
        {
            double dx = hull[i].X - hull[(i+1)%hull.size()].X,
                   dy = hull[i].Y - hull[(i+1)%hull.size()].Y;
            result += hypot(dx, dy);
            if(hull[i].Y < bottomleft.Y or
              (hull[i].Y == bottomleft.Y and hull[i].X < bottomleft.X))
                bottomleft = hull[i], bottomleft_idx = i;
        }
        cout << result << "\n";
        uint32_t first = true;
        for(uint32_t i = bottomleft_idx; i != bottomleft_idx or (first--); i = (i+1)%hull.size())
            cout << buckets[(1<<14)+hull[i].X][hull[i].Y]+1 << " ";
        cout << "\n\n";
    }
}
