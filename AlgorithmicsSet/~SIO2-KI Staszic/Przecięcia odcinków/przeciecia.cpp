#include <bits/stdc++.h>

#ifdef _WIN32
#define getchar_unlocked getchar
#define putchar_unlocked putchar
#endif

using namespace std;

struct unlocked_cin
{
    unlocked_cin& operator>> (char& x)
    {
        x = getchar_unlocked();
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_unsigned<T>::value, unlocked_cin&>::type
    operator>> (T& x)
    {
        char lchar; x = 0;
        while(isspace(lchar = getchar_unlocked())) {}
        do {
            x *= 10, x += lchar - '0';
        } while(isdigit(lchar = getchar_unlocked()));
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_signed<T>::value, unlocked_cin&>::type
    operator>> (T& x)
    {
        bool s = false; x = 0;
        char lchar;
        while(isspace(lchar = getchar_unlocked())) {}
        if(lchar == '-')
            s = true;
        else
            x += lchar - '0';
        while(isdigit(lchar = getchar_unlocked()))
            x *= 10, x += lchar - '0';
        if(s) x = -x;
        return *this;
    }
} ucin;

namespace geometry
{
    struct vec2d { int64_t x, y; };
    vec2d operator+ (const vec2d& a, const vec2d& b) { return {a.x+b.x, a.y+b.y}; }
    vec2d operator- (const vec2d& a) { return {-a.x, -a.y}; }
    vec2d operator- (const vec2d& a, const vec2d& b) { return a + (-b); }
    int64_t operator* (const vec2d& a, const vec2d& b) { return a.x*b.x + a.y*b.y; }
    int64_t operator^ (const vec2d& a, const vec2d& b) { return a.x*b.y - a.y*b.x; }
    int64_t operator+ (const vec2d& a) { return a.x*a.x + a.y*a.y; }

    template<typename T>
    int sgn(T x) { return int(x > 0) - int(x < 0); }
    int64_t ori(const vec2d& a, const vec2d& b, const vec2d& c)
        { return (c.y-a.y) * (b.x-a.x) - (b.y-a.y) * (c.x-a.x); }

    // on segment
    bool ons(const vec2d& a, const vec2d& b, const vec2d& p)
    {
        return (b.x <= max(a.x, p.x) and b.x >= min(a.x, p.x) and
                b.y <= max(a.y, p.y) and b.y >= min(a.y, p.y));
    }
    bool intersects(const vec2d& a, const vec2d& b, const vec2d& c, const vec2d& d)
    {
        int64_t o1 = ori(a, b, c), o2 = ori(a, b, d),
                o3 = ori(c, d, a), o4 = ori(c, d, b);
        if(sgn(o1) != sgn(o2) and sgn(o3) != sgn(o4))
            return true;
        else if((o1 == 0 and ons(a, c, b)) or
                (o2 == 0 and ons(a, d, b)) or
                (o3 == 0 and ons(c, a, d)) or
                (o4 == 0 and ons(c, b, d)))
            return true;
        else
            return false;
    }
}

template<typename Stream>
Stream& operator>> (Stream& in, geometry::vec2d& v) { return in >> v.x >> v.y; }

int main()
{
    uint32_t n;
    ucin >> n;
    while(n --> 0)
    {
        geometry::vec2d a, b, c, d;
        ucin >> a >> b >> c >> d;
        if(geometry::intersects(a, b, c, d))
            puts("TAK");
        else
            puts("NIE");
    }
}
