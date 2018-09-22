#include <bits/stdc++.h>

using namespace std;

template<typename T>
T gcd(T a, T b) { return __gcd(a, b); }

template<typename T>
struct gcdext_result { T d, x, y; };

template<typename T>
gcdext_result<T> gcdext(T a, T b)
{
    if(a == 0)
        return {b, 0, 1};
    gcdext_result<T> next = gcdext(b % a, a);
    return {next.d, next.y - (b/a)*next.x, next.x};
}
template<typename T>
gcdext_result<T> sgn_gcdext(T a, T b)
{
    auto r = gcdext(abs(a), abs(b));
    if(a < 0) r.x = -r.x;
    if(b < 0) r.y = -r.y;
    return r;
}


bool solve(int64_t k, int64_t n, int64_t dx, int64_t dy)
{
    if(n > k) swap(n, k);
    if(n == 0)
        return dx%k == 0 and dy%k == 0;
    auto rx = sgn_gcdext(k, n);
    if(dx % rx.d != 0)
        return false;
    else
    {
        rx.x *= dx / rx.d;
        rx.y *= dx / rx.d;
    }
    bool ok = false;
    for(int64_t p = -256; p <= 256; p++)
    {
        int64_t a, b;
        a = rx.x + (n / rx.d) * p;
        b = rx.y - (k / rx.d) * p;

        auto ry = sgn_gcdext(2*k, 2*n);
        if((dy - b*k - a*n) % ry.d != 0)
            continue;
        else
        {
            ry.x *= (dy - b*k - a*n) / ry.d;
            ry.y *= (dy - b*k - a*n) / ry.d;
        }
        if(dx == a*k + b*n and dy == b*k + a*n + ry.x * 2*k + ry.y * 2*n)
            ok = true;
    }
    return ok;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t t;
    cin >> t;
    while(t --> 0)
    {
        int64_t k, n, x1, y1, x2, y2;
        cin >> k >> n >> x1 >> y1 >> x2 >> y2;
        int64_t dx = x2 - x1, dy = y2 - y1;
        cout << (solve(k, n, dx, dy) ? "TAK\n" : "NIE\n");
    }
}
