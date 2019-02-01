#include <bits/stdc++.h>

using namespace std;

namespace geometry
{
    struct vec2d { int64_t x, y; };
    vec2d operator+ (vec2d a, vec2d b) { return {a.x+b.x, a.y+b.y}; }
    vec2d operator- (vec2d a) { return {-a.x, -a.y}; }
    vec2d operator- (vec2d a, vec2d b) { return a + (-b); }
    int64_t operator* (vec2d a, vec2d b) { return a.x*b.x + a.y*b.y; }
    int64_t operator^ (vec2d a, vec2d b) { return a.x*b.y - a.y*b.x; }
    int64_t operator+ (vec2d a) { return a.x*a.x + a.y*a.y; }

    template<typename T>
    int sgn(T x) { return int(x > 0) - int(x < 0); }
    int64_t ori(vec2d a, vec2d b, vec2d c)
        { return (c.y-a.y) * (b.x-a.x) - (b.y-a.y) * (c.x-a.x); }

    vector<vec2d> find_convex_hull(vector<vec2d> points)
    {
        auto min_it = min_element(points.begin(), points.end(), [](vec2d a, vec2d b) {
            return make_pair(a.x, a.y) < make_pair(b.x, b.y);
        });
        iter_swap(points.begin(), min_it);
        auto s = points.front();
        sort(points.begin()+1, points.end(), [s](vec2d a, vec2d b) {
            auto v = (a - s) ^ (b - s);
            return v == 0 ? +(a - s) < +(b - s) : v > 0;
        });
        points.push_back(points[0]);
        vector<vec2d> hull = {points[0], points[1]};
        for(uint32_t i = 2; i < points.size(); i++)
        {
            auto p = points[i];
            while(hull.size() > 2 and ori(hull.end()[-2]-s, hull.end()[-1]-s, p-s) <= 0)
                hull.pop_back();
            hull.push_back(p);
        }
        hull.pop_back();
        return hull;
    }
}

const size_t N = 1526;
int64_t A[N][N]; uint32_t O[N][N];
vector<geometry::vec2d> P;

void compute(uint32_t n, uint32_t t, uint32_t I, uint32_t L, uint32_t R, uint32_t oL, uint32_t oR)
{
    uint32_t _i = (L + R + 1) / 2;
    uint32_t i = (I+_i)%n;
    A[t][i] = numeric_limits<int64_t>::min();
    O[t][i] = -1u;
    for(uint32_t _i1 = oL; _i1 <= oR; _i1++)
    {
        if(_i1 < _i)
        {
            uint32_t i1 = (I+_i1)%n;
            int64_t v = A[t-1][i1] + ((P[i1] - P[I]) ^ (P[i] - P[I]));
            if(v > A[t][i])
                A[t][i] = v, O[t][i] = _i1;
        }
    }
    if(L < R and O[t][i] != -1u)
    {
        if(L < _i) compute(n, t, I, L, _i-1, oL, O[t][i]);
        if(_i < R) compute(n, t, I, _i+1, R, O[t][i], oR);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    P.resize(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> P[i].x >> P[i].y;
    P = geometry::find_convex_hull(P);
    n = P.size();
    k = min(k, n);
    vector<uint32_t> J(n);
    iota(J.begin(), J.end(), 0);
    shuffle(J.begin(), J.end(), mt19937(42));
    uint32_t jp = min(n, (n/k)*8);
    int64_t result = 0;
    for(uint32_t j = 0; j < jp; j++)
    {
        fill(&A[0][0], &A[k+1][0], 0);
        fill(&O[0][0], &O[k+1][0], 0);
        for(uint32_t t = 3; t <= k; t++)
            compute(n, t, J[j], 1, n-1, 1, n-1);
        for(uint32_t i = 0; i < n; i++)
            result = max(result, A[k][i]);
    }
    if(result % 2)
        cout << result/2 << ".5";
    else
        cout << result/2 << ".0";
}
