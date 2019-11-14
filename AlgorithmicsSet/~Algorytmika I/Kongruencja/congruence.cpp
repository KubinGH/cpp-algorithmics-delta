#include <bits/stdc++.h>

using namespace std;

struct egcd_res { int64_t d, x, y; };
egcd_res egcd(int64_t a, int64_t b)
{
    if(a == 0)
        return {b, 0, 1};
    auto r = egcd(b % a, a);
    return {r.d, r.y - (b/a)*r.x, r.x};
}

template<typename T>
T umod(T x, T n) { x %= n; return x < 0 ? x + n : x; }

int main()
{
    int64_t a, b, m;
    cin >> a >> b >> m;

    auto r = egcd(a, m);
    int64_t d = r.d;

    if(b % d == 0)
    {
        int64_t x = b/d*r.x;
        x = (x%(m/d) + m/d) % (m/d);
        cout << x;
    }
    else
        cout << "NIE";
}
