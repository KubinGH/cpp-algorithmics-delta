#include <bits/stdc++.h>

// -*- ktl/math/egcd.cpp -*-

#include <cstdint>

using std::int64_t;

struct egcd_res { int64_t d, x, y; };
egcd_res egcd(int64_t a, int64_t b)
{
    if(a == 0)
        return {b, 0, 1};
    auto r = egcd(b % a, a);
    return {r.d, r.y - (b/a)*r.x, r.x};
}

// -$- ktl/math/egcd.cpp -$-


using namespace std;

egcd_res signed_egcd(int64_t a, int64_t b)
{
    auto r = egcd(abs(a), abs(b));
    if(a < 0) r.x = -r.x;
    if(b < 0) r.y = -r.y;
    return r;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t t;
    cin >> t;
    while(t --> 0)
    {
        int64_t x1, y1, x2, y2, x, y;
        cin >> x1 >> y1 >> x2 >> y2 >> x >> y;

        int64_t A = INT64_MIN, B = INT64_MIN;
        auto maybe = [&](int64_t a, int64_t b) {
            if(a*x1 + b*x2 == x and a*y1 + b*y2 == y)
                A = a, B = b;
        };

        for(bool e : {0, 1})
        {
            auto r = signed_egcd(x1, x2);
            auto d = r.d ? r.d : x, a0 = r.x * x/d, b0 = r.y * x/d;
            auto k = x2*y1 != x1*y2 ? (y - a0*y1 - b0*y2)*d / (x2*y1 - x1*y2) : 0;
            auto a = a0 + k*x2/d, b = b0 - k*x1/d;
            if(e) swap(a, b);
            maybe(a, b);
            swap(x1, y1); swap(x2, y2); swap(x, y);
        }

        if(A != INT64_MIN and B != INT64_MIN)
            cout << "TAK " << A << ' ' << B << '\n';
        else
            cout << "NIE\n";
    }
}
