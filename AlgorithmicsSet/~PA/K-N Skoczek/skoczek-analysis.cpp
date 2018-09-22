#include <bits/stdc++.h>

using namespace std;

typedef pair<int64_t, int64_t> pt;
typedef tuple<int64_t, int64_t, int64_t, int64_t> dt;

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
    if(n == 0 and k == 0)
        return dx == 0 and dy == 0;
    if(n == 0)
        return dx%k == 0 and dy%k == 0;
    auto r = sgn_gcdext(k, n);
    if(dx % r.d != 0)
        return false;
    int64_t g = gcd((k*k/r.d - n*n/r.d), 2*r.d);
    int64_t a = 0;
    a += (r.y%g)*(k%g); a %= g;
    a += (r.x%g)*(n%g); a %= g;
    a *= dx/r.d; a %= g;
    a -= dy; a %= g;
    return a % g == 0;
}

int main()
{
    int64_t n, k;
    for(n = 0; n <= 16; n++) for(k = n; k <= 16; k++)
    {
        cout << " === " << n << " " << k << " === " << endl;
        set<pair<int64_t, int64_t>> S;
        queue<pair<int64_t, int64_t>> Q;
        Q.emplace(20, 20);
        auto checkaedd = [&](int64_t x, int64_t y) {
            if(S.find({x, y}) == S.end())
                S.emplace(x, y), Q.emplace(x, y);
        };
        while(not Q.empty())
        {
            int64_t x, y; tie(x, y) = Q.front(); Q.pop();
            if(x < -200 or x > 300 or y < -200 or y > 300) continue;
            checkaedd(x+k, y+n);
            checkaedd(x+n, y+k);
            checkaedd(x-k, y+n);
            checkaedd(x-n, y+k);
            checkaedd(x+k, y-n);
            checkaedd(x+n, y-k);
            checkaedd(x-k, y-n);
            checkaedd(x-n, y-k);
        }
        for(int64_t y = -100; y < 100; y++)
        {
            for(int64_t x = -100; x < 100; x++)
            {
                assert((S.find({x, y}) != S.end()) == solve(k, n, x-20, y-20));
                //cout << ((S.find({x, y}) != S.end()) ? (x==20 and y==20 ? '$' : '@') : ' ');
            }
            //cout << endl;
        }
        cout << endl;
    }
    /*
    const int64_t N = 5;
    set<dt> S;
    map<pt, set<pt>> M;
    queue<dt> Q;
    Q.emplace(0, 0, 0, 0);
    auto checkaedd = [&](int64_t a, int64_t b, int64_t c, int64_t d) {
        if(S.find(dt{a, b, c, d}) == S.end())
            S.emplace(a, b, c, d), Q.emplace(a, b, c, d);
    };
    while(not Q.empty())
    {
        int64_t a, b, c, d; tie(a, b, c, d) = Q.front(); Q.pop();
        if(a < -N or a > N or b < -N or b > N or
           c < -N or c > N or d < -N or d > N) continue;
        M[{a, b}].emplace(c, d);
        checkaedd(a+1, b, c, d+1);
        checkaedd(a, b+1, c+1, d);
        checkaedd(a+1, b, c, d-1);
        checkaedd(a, b+1, c-1, d);
        checkaedd(a-1, b, c, d+1);
        checkaedd(a, b-1, c+1, d);
        checkaedd(a-1, b, c, d-1);
        checkaedd(a, b-1, c-1, d);
    }
    for(auto p : M)
    {
        cout << p.first.first << ", " << p.first.second << ": ";
        for(auto q : M[p.first])
        {
            cout << q.first << ", " << q.second << "; ";
            assert((q.first - p.first.second) % 2 == 0);
            assert((q.second - p.first.first) % 2 == 0);
        }
        cout << endl << endl;
    }
    */
}
