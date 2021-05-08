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
int64_t dot(vec a, vec b)
{
    return (conj(a) * b).real();
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

int intersects(int64_t a, int64_t b, int64_t c, int64_t d)
{
    if(a > b) swap(a, b);
    if(c > d) swap(c, d);
    return max(a, c) <= min(b, d);
}

bool intersects(vec p1, vec p2, vec q1, vec q2)
{
    int o11 = ori(p1, p2, q1), o12 = ori(p1, p2, q2),
        o21 = ori(q1, q2, p1), o22 = ori(q1, q2, p2);

    if(o11 == 0 and o12 == 0)
        return intersects(p1.real(), p2.real(), q1.real(), q2.real())
            && intersects(p1.imag(), p2.imag(), q1.imag(), q2.imag());
    return o11 != o12 and o21 != o22;
}

bool contains(int64_t a, int64_t b, int64_t c)
{
    if(a > b) swap(a, b);
    return a <= c and c <= b;
}

bool contains(vec p1, vec p2, vec q)
{
    return ori(p1, p2, q) == 0 and contains(p1.real(), p2.real(), q.real())
                               and contains(p1.imag(), p2.imag(), q.imag());
}

int point_in_polygon(const vector<vec>& v, vec p)
{
    const size_t n = v.size();
    for(size_t i = 0; i < n; i++)
        if(contains(v[i], v[i+1 == n ? 0 : i+1], p))
            return 0;

    constexpr static vec offset(2e9, 1);
    int c = 0;
    for(size_t i = 0; i < n; i++)
        c += intersects(v[i], v[i+1==n ? 0 : i+1], p, p + offset);

    return c % 2 ? +1 : -1;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vec> vertices(n);
    for(auto& v : vertices)
        cin >> v;

    while(m --> 0)
    {
        vec p;
        cin >> p;
        auto s = point_in_polygon(vertices, p);
        if(s == +1)
            cout << "INSIDE\n";
        else if(s == -1)
            cout << "OUTSIDE\n";
        else
            cout << "BOUNDARY\n";
    }
}
