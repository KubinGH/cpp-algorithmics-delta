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
    int64_t m1, m2, a1, a2;
    cin >> m1 >> m2 >> a1 >> a2;
    auto r = egcd(m1, m2);
    cout << umod(m1*umod(r.x*(a2-a1), m1*m2) + a1, m1*m2);
}
