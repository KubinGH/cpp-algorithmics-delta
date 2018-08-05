#include <complex>
#define X real()
#define Y imag()

using namespace std;

template<typename T>
T cross(const complex<T>& a, const complex<T>& b)
{
    return a.X * b.Y - b.X * a.Y;
}
int64_t sign(int64_t x) { return (x >= 0) - (x <= 0); }
// orientation
template<typename T>
T ori(const complex<T>& a, const complex<T>& b, const complex<T>& c)
{
    return sign((c.Y-a.Y) * (b.X-a.X) - (b.Y-a.Y) * (c.X-a.X));
}
// on segment
template<typename T>
bool ons(const complex<T>& a, const complex<T>& b, const complex<T>& p)
{
    return (b.X <= max(a.X, p.X) and b.X >= min(a.X, p.X) and
            b.Y <= max(a.Y, p.Y) and b.Y >= min(a.Y, p.Y));
}
template<typename T>
bool intersects(const complex<T>& a, const complex<T>& b,
                const complex<T>& c, const complex<T>& d)
{
    int64_t o1 = ori(a, b, c), o2 = ori(a, b, d),
            o3 = ori(c, d, a), o4 = ori(c, d, b);
    if(o1 != o2 and o3 != o4)
        return true;
    else if((o1 == 0 and ons(a, c, b)) or
            (o2 == 0 and ons(a, d, b)) or
            (o3 == 0 and ons(c, a, d)) or
            (o4 == 0 and ons(c, b, d)))
        return true;
    else
        return false;
}
