#include <bits/stdc++.h>

using namespace std;

inline int64_t gcd(int64_t a, int64_t b) { return __gcd(a, b); }

struct gcdext_result
{
    int64_t d, x, y;
    gcdext_result() {}
    gcdext_result(int64_t d, int64_t x, int64_t y) : d(d), x(x), y(y) {}
};

gcdext_result gcdext(int64_t a, int64_t b)
{
    if(a == 0)
        return {b, 0, 1};
    gcdext_result next = gcdext(b % a, a);
    return {next.d, next.y - (b/a)*next.x, next.x};
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int64_t a, b, c, d;
    while(cin >> a >> b >> c >> d)
    {
        c = d - c;
        gcdext_result r = gcdext(a, b);
        int64_t k = c / r.d;
        int64_t p = abs(c - k*r.d);
        while(true)
        {
            int64_t p1 = abs(c - (k-1)*r.d), p2 = abs(c - (k+1)*r.d);
            if(p1 < p)
                k--, p = p1;
            else if(p2 < p)
                k++, p = p2;
            else
                break;
        }
        cout << r.x * k << " " << r.y * k << "\n";
    }
}
