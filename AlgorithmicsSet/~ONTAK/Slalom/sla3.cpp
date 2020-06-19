#include <bits/stdc++.h>

using namespace std;


struct vec2d { int64_t x, y; };
vec2d operator+ (vec2d a, vec2d b) { return {a.x+b.x, a.y+b.y}; }
vec2d operator- (vec2d a) { return {-a.x, -a.y}; }
vec2d operator- (vec2d a, vec2d b) { return a + (-b); }
int64_t operator* (vec2d a, vec2d b) { return a.x*b.x + a.y*b.y; }
int64_t operator^ (vec2d a, vec2d b) { return a.x*b.y - a.y*b.x; }
int64_t operator+ (vec2d a) { return a.x*a.x + a.y*a.y; }

template<typename T>
int sgn(T x) { return int(x > 0) - int(x < 0); }
int64_t ori(vec2d a, vec2d b, vec2d c) { return sgn((b - a) ^ (c - a)); }
int64_t area(vec2d a, vec2d b, vec2d c) { return (b - a) ^ (c - b); }

struct segment2d { vec2d A, B; };

ostream& operator<< (ostream& out, const vec2d& v)
{
    return out << '[' << v.x << ',' << ' ' << v.y << ']';
}
ostream& operator<< (ostream& out, const segment2d& s)
{
    return out << '[' << s.A << '-' << '-' << s.B << ']';
}

bool ons(const vec2d& A, const vec2d& B, const vec2d& P)
{
    return ori(A, B, P) == 0 and
           min(A.x, B.x) <= P.x and P.x <= max(A.x, B.x) and
           min(A.y, B.y) <= P.y and P.y <= max(A.y, B.y);
}
bool intersects(const segment2d& P, const segment2d& Q)
{
    int p1 = ori(P.A, P.B, Q.A), p2 = ori(P.A, P.B, Q.B),
        q1 = ori(Q.A, Q.B, P.A), q2 = ori(Q.A, Q.B, P.B);
    if(p1 != p2 and q1 != q2)
        return true;
    else if(ons(P.A, P.B, Q.A) or ons(P.A, P.B, Q.B) or
            ons(Q.A, Q.B, P.A) or ons(Q.A, Q.B, P.B))
        return true;
    else
        return false;
}


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

    auto through = [&](size_t i, size_t p, size_t j, size_t q, size_t k) {
        return intersects({{X[i][p], Y[i]}, {X[j][q], Y[j]}}, {{X[k][0], Y[k]}, {X[k][1], Y[k]}});
    };

    vector<array<long double, 2>> Q(n+2);
    vector<array<pair<size_t, size_t>, 2>> I(n+2);

    for(size_t i = 1; i < n+2; i++)
      for(size_t p = 0; p < 2; p++)
    {
        Q[i][p] = 1e18;
        for(size_t j = 0; j < i; j++)
            for(size_t q = 0; q < 2; q++)
        {
            bool ok = true;
            for(size_t k = j+1; ok and k < i; k++)
                ok &= through(i, p, j, q, k);
            if(ok)
            {
                auto x = Q[j][q] + hypotl(X[i][p]-X[j][q], Y[i]-Y[j]);
                if(x+1e-9 < Q[i][p])
                    Q[i][p] = x, I[i][p] = {j, q};
            }
        }
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
