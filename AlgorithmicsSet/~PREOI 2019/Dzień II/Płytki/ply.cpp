#include <bits/stdc++.h>

using namespace std;

const size_t N = 16;

template<typename T>
struct _vec2d
{
    T x, y;
    T operator+ () { return x*x + y*y; }
    _vec2d operator- () { return {-x, -y}; }
    _vec2d operator+ (_vec2d o) { return {x+o.x, y+o.y}; }
    _vec2d operator- (_vec2d o) { return *this + -o; }
    _vec2d operator^ (_vec2d o) { return x*o.y - y*o.x; }
    _vec2d operator* (_vec2d o) { return x*o.x + y*o.y; }
};

template<typename T>
ostream& operator<< (ostream& out, _vec2d<T> o)
    { return out << "(" << o.x << ", " << o.y << ")"; }
template<typename T>
istream& operator>> (istream& in, _vec2d<T>& o)
    { return in >> o.x >> o.y; }

using vec2d = _vec2d<int64_t>;
using polygon = vector<vec2d>;

int64_t parawidth(const polygon& poly)
{
    int64_t minX = INT64_MAX, maxX = INT64_MIN;
    for(uint32_t i = 0; i < poly.size(); i++)
        minX = min(minX, poly[i].x), maxX = max(maxX, poly[i].x);
    return maxX - minX;
}
int64_t paraheight(const polygon& poly)
{
    int64_t minY = INT64_MAX, maxY = INT64_MIN;
    for(uint32_t i = 0; i < poly.size(); i++)
        minY = min(minY, poly[i].y), maxY = max(maxY, poly[i].y);
    return maxY;
}

long double segment_at_y(vec2d u, vec2d v, int64_t y)
{
    return (long double)(v.x*(u.y - y) + u.x*(y - v.y)) / (u.y - v.y);
}

long double min_sticky(const polygon& L, const polygon& R)
{
    const uint32_t n = L.size(), m = R.size();
    const int64_t H = paraheight(R);

    long double P = 0;
    for(uint32_t e = 0, f = 1; e == m-1 or R[e+1].y < H; e--)
    {
        while(L[f+1].y < R[e].y)
            f++;
        P = max(P, segment_at_y(L[f], L[f+1], R[e].y) - R[e].x);
        if(e == 0) e = m;
    }
    for(uint32_t f = 1, e = 0, e1; L[f-1].y < H; f++)
    {
        e1 = (e ? e-1 : m-1);
        while(R[e1].y < H and R[e1].y < L[f].y)
            e = e1, e1 = (e ? e-1 : m-1);
        P = max(P, L[f].x - segment_at_y(R[e], R[e1], L[f].y));
    }
    int64_t minX1 = INT64_MAX, maxX1 = INT64_MIN;
    for(uint32_t i = 0; i < m; i++)
        minX1 = min(minX1, R[i].x), maxX1 = max(maxX1, R[i].x);
    int64_t minX2 = INT64_MAX, maxX2 = INT64_MIN;
    for(uint32_t i = 0; i < n; i++)
        minX2 = min(minX2, L[i].x), maxX2 = max(maxX2, L[i].x);
    return max(maxX1 + P, (long double)maxX2) -
           min(minX1 + P, (long double)minX2);
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static polygon sheets[N];
    static int64_t width[N];
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t k;
        cin >> k;
        sheets[i].resize(k);
        for(uint32_t j = 0; j < k; j++)
            cin >> sheets[i][j];
        width[i] = parawidth(sheets[i]);
    }

    static long double min_cost[N][N];
    for(uint32_t i = 0; i < n; i++)
        for(uint32_t j = 0; j < n; j++)
            min_cost[i][j] = min_sticky(sheets[i], sheets[j]) - width[i];
    static long double Q[1 << N][N];
    fill(&Q[0][0], &Q[1<<N][0], 1e10);

    for(uint32_t a = 0; a < n; a++)
        Q[1u << a][a] = width[a];
    for(uint32_t m = 3; m < (1u << n); m++) if(m & (m-1))
      for(uint32_t b = 0; b < n; b++) if((m & (1u << b)))
    {
        long double& q = Q[m][b];
        for(uint32_t a = 0; a < n; a++) if((m & (1u << a)) and a != b)
            q = min(q, Q[m ^ (1u << b)][a] + min_cost[a][b]);
    }

    long double result = LDBL_MAX;
    for(uint32_t b = 0; b < n; b++)
        result = min(result, Q[(1u<<n)-1][b]);

    cout << fixed << setprecision(10) << (double)result;
}
