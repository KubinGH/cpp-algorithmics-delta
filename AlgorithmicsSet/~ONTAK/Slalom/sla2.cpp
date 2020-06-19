#include <bits/stdc++.h>

using namespace std;

struct vec2d { int64_t x, y; };
vec2d operator+ (vec2d a, vec2d b) { return {a.x+b.x, a.y+b.y}; }
vec2d operator- (vec2d a) { return {-a.x, -a.y}; }
vec2d operator- (vec2d a, vec2d b) { return a + (-b); }
int64_t operator* (vec2d a, vec2d b) { return a.x*b.x + a.y*b.y; }
int64_t operator^ (vec2d a, vec2d b) { return a.x*b.y - a.y*b.x; }
int64_t operator+ (vec2d a) { return a.x*a.x + a.y*a.y; }
bool operator== (vec2d a, vec2d b) { return a.x == b.x and a.y == b.y; }
ostream& operator<< (ostream& out, const vec2d& v)
{
    return out << '[' << v.x << ',' << ' ' << v.y << ']';
}

template<typename T>
int sgn(T x) { return int(x > 0) - int(x < 0); }
int64_t ori(vec2d a, vec2d b, vec2d c) { return sgn((b - a) ^ (c - a)); }
int64_t area(vec2d a, vec2d b, vec2d c) { return (b - a) ^ (c - b); }

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<array<int64_t, 2>> X(n+2);
    vector<int64_t> Y(n+2);

    cin >> X[0][0] >> Y[0] >> X[n+1][0] >> Y[n+1];
    X[0][1] = X[0][0]; X[n+1][1] = X[n+1][0];
    for(size_t i = 1; i < n+1; i++)
        cin >> X[i][0] >> X[i][1] >> Y[i];

    vector<array<long double, 2>> Q(n+2);
    vector<array<pair<size_t, size_t>, 2>> I(n+2);

    auto maybe = [&](size_t i, size_t p, size_t j, size_t q) {
        auto x = Q[j][q] + hypotl(X[i][p]-X[j][q], Y[i]-Y[j]);
        if(x+1e-9 < Q[i][p])
            Q[i][p] = x, I[i][p] = {j, q};
    };

    for(size_t i = 1; i < n+2; i++)
      for(size_t p = 0; p < 2; p++)
    {
        Q[i][p] = 1e18;
        vec2d l{}, r{};

        size_t k0 = i, k1 = i;
        for(size_t j = i; j --> 0; )
        {
            vec2d u {X[j][0]-X[i][p], Y[j]-Y[i]}, v {X[j][1]-X[i][p], Y[j]-Y[i]};
            if((u ^ l) >= 0) l = u;
            if((r ^ v) >= 0) r = v;
            if((r ^ l) < 0)  break;

            if(u == l) k0 = j;
            if(v == r) k1 = j;
        }
        maybe(i, p, k0, 0);
        maybe(i, p, k1, 1);
    }

    size_t i = n+1, p = 0;
    vector<pair<int, int>> order;
    while(true)
    {
        order.emplace_back(X[i][p], Y[i]);
        if(not i) break;
        tie(i, p) = I[i][p];
    }

    reverse(order.begin(), order.end());

    cout << order.size() << endl;
    for(auto c : order)
        cout << c.first << ' ' << c.second << '\n';
}
