#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct _vec2d
{
    T x, y;
    int64_t operator+ () { return x*x + y*y; }
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
using vec2d_f = _vec2d<double>;
using polygon = vector<vec2d>;
using segment = pair<vec2d, vec2d>;

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
    return maxY - minY;
}

double segment_at_y(vec2d _u, vec2d _v, double y)
{
    if(_u.x == _v.x) return _u.y;
    vec2d_f u = {(double)_u.x, (double)_u.y},
            v = {(double)_v.x, (double)_v.y};
    double a = (v.y - u.y) / (v.x - u.x);
    double b = u.y - u.x*a;
    return (y - b) / a;
}

double min_sticky(const polygon& base, const polygon& ext)
{
    const uint32_t n = base.size(), m = ext.size();
    const int64_t H = paraheight(ext);

    double P = 0;
    for(uint32_t e = 0, f = 1; e == m-1 or ext[e+1].y < H; e--)
    {
        while(base[f+1].y < ext[e].y)
            f++;
        P = max(P, segment_at_y(base[f], base[f+1], ext[e].y) - ext[e].x);
        if(e == 0) e = m;
    }
    for(uint32_t f = 1, e = 0; ext[f-1].y < H; f++)
    {
        uint32_t e1;
        while(ext[e1 = (e == 0 ? m-1 : e-1)].y < base[f].y)
            e = e1;
        P = max(P, base[f].x - segment_at_y(ext[e], ext[e1], base[f].y));
    }
    double minX = 0, maxX = 0;
    for(uint32_t i = 0; i < n; i++)
        minX = min(minX, (double)base[i].x), maxX = max(maxX, (double)base[i].x);
    for(uint32_t i = 0; i < m; i++)
        minX = min(minX, ext[i].x+P), maxX = max(maxX, ext[i].x+P);

    return maxX - minX;
}



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<polygon> sheets(n);
    vector<int64_t> width(n);
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t k;
        cin >> k;
        sheets[i].resize(k);
        for(uint32_t j = 0; j < k; j++)
            cin >> sheets[i][j];
        width[i] = parawidth(sheets[i]);
    }

    vector<vector<double>> max_overlap(n, vector<double>(n));
    for(uint32_t i = 0; i < n; i++)
        for(uint32_t j = 0; j < n; j++)
            max_overlap[i][j] = (width[i] + width[j]) - min_sticky(sheets[i], sheets[j]);

    vector<uint32_t> P(n);
    iota(P.begin(), P.end(), 0);
    double result = numeric_limits<double>::max();
    do {
        double curr = width[P[0]];
        for(uint32_t i = 1; i < n; i++)
            curr += width[P[i]] - max_overlap[P[i-1]][P[i]];
        result = min(result, curr);
    } while(next_permutation(P.begin(), P.end()));

    cout << fixed << setprecision(10) << result;
}
