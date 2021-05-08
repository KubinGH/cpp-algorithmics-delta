#include <bits/stdc++.h>

using namespace std;

using vec = complex<int64_t>;

istream& operator>> (istream& in, vec& v)
{
    int64_t x, y;
    in >> x >> y;
    v = vec(x, y);
    return in;
}

int64_t cross(vec a, vec b)
{
    return (conj(a) * b).imag();
}

template<typename T>
int sgn(T x)
{
    return (x > 0) - (x < 0);
}

int ori(vec a, vec p, vec q)
{
    return sgn(cross(p - a, q - a));
}

template<int level = +1>
vector<vec> convex_hull(vector<vec> points)
{
    sort(points.begin(), points.end(), [](vec a, vec b) {
        return pair(a.real(), a.imag()) < pair(b.real(), b.imag());
    });
    vector<vec> hull;
    for(size_t rep = 0; rep < 2; rep++)
    {
        for(auto p : points)
        {
            while(hull.size() >= 2 and ori(hull.end()[-2], hull.end()[-1], p) < level)
                hull.pop_back();
            hull.push_back(p);
        }
        if(not rep) points.pop_back(), reverse(points.begin(), points.end());
    }
    hull.pop_back();
    return hull;
}

int main()
{
    size_t n;
    cin >> n;

    vector<vec> points(n);
    for(auto& p : points)
        cin >> p;

    auto hull = convex_hull<0>(points);

    cout << hull.size() << endl;
    for(auto p : hull)
        cout << p.real() << ' ' << p.imag() << '\n';
}
