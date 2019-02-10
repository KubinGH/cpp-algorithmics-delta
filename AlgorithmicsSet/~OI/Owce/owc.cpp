#include <bits/stdc++.h>

using namespace std;

struct vec2d { int32_t x, y; };
vec2d operator+ (vec2d a, vec2d b) { return {a.x + b.x, a.y + b.y}; }
vec2d operator- (vec2d a) { return {-a.x, -a.y}; }
vec2d operator- (vec2d a, vec2d b) { return a + (-b); }
int32_t operator* (vec2d a, vec2d b) { return a.x*b.x + a.y*b.y; }
int32_t operator^ (vec2d a, vec2d b) { return a.x*b.y - a.y*b.x; }
int32_t ori(vec2d a, vec2d b, vec2d c) { return (b - a) ^ (c - a); }

istream& operator>> (istream& in, vec2d& v) { return in >> v.x >> v.y; }
ostream& operator<< (ostream& out, vec2d& v) { return out << "{" << v.x << ", " << v.y << "}"; }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k, m;
    cin >> n >> k >> m;

    vector<vec2d> vertices(2*n);
    for(uint32_t i = 0; i < n; i++)
        cin >> vertices[i];
    copy(vertices.begin(), vertices.begin()+n, vertices.begin()+n);
    reverse(vertices.begin(), vertices.end());

    vector<vec2d> points(k);
    for(uint32_t i = 0; i < k; i++)
        cin >> points[i];

    auto valid = [&](vec2d a, vec2d b, vec2d c) {
        bool z = true;
        for(auto p : points)
            if(ori(a, b, p) > 0 and ori(b, c, p) > 0 and ori(c, a, p) > 0)
                z ^= 1;
        for(auto p : points)
            if(ori(a, b, p) == 0 or ori(b, c, p) == 0 or ori(c, a, p) == 0)
                z = false;
        return z;
    };

    vector<vector<uint32_t>> Q(n, vector<uint32_t>(n));
    for(uint32_t i = 0; i < n; i++)
        Q[i][i] = 1, Q[i][(i+1)%n] = 1;
    for(uint32_t d = 2; d < n; d++)
    {
        for(uint32_t a = 0, c = a+d; a < n; a++, c++)
        {
            for(uint32_t b = a+1; b < c; b++)
            {
                if(valid(vertices[a], vertices[b], vertices[c]))
                {
                    Q[a%n][c%n] += Q[a%n][b%n] * Q[b%n][c%n];
                    Q[a%n][c%n] %= m;
                }
            }
        }
    }
    cout << Q[0][n-1];
}
