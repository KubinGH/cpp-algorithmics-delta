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
    return x > 0 ? +1 : (x < 0 ? -1 : 0);
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

    if(o11 == 0 and o12 == 0) // <=> o21 == 0 and o22 == 0
        return intersects(p1.real(), p2.real(), q1.real(), q2.real())
            && intersects(p1.imag(), p2.imag(), q1.imag(), q2.imag());
    return o11 != o12 and o21 != o22;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t t;
    cin >> t;

    while(t --> 0)
    {
        vec p1, p2, q1, q2;
        cin >> p1 >> p2 >> q1 >> q2;
        cout << (intersects(p1, p2, q1, q2) ? "YES\n" : "NO\n");
    }
}
