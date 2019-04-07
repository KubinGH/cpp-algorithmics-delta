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
int64_t ori(vec2d a, vec2d b, vec2d c) { return (b - a) ^ (c - a); }
int64_t area(vec2d a, vec2d b, vec2d c) { return (b - a) ^ (c - b); }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;

    vector<vec2d> vertices(n+1);
    for(uint32_t i = 0; i < n; i++)
        cin >> vertices[i].x >> vertices[i].y;
    vertices.back() = vertices.front();

    int64_t result = 0;
    for(uint32_t i = 0; i < n; i++)
        result += area({0, 0}, vertices[i], vertices[i+1]);

    cout << (abs(result) + 1) / 2;
}
