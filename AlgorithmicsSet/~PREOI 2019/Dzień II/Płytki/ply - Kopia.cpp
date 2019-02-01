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

int sgn(int64_t x) { return x < 0 ? -1 : x > 0; }
template<typename T>
int64_t ori(_vec2d<T> a, _vec2d<T> b, _vec2d<T> c) { return (b ^ a) ^ (c - a); }
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

double min_sticky(const vector<vec2d>& base, const vector<vec2d>& ext)
{
    const uint32_t n = base.size(), m = ext.size();
    const int64_t H = paraheight(ext);
//cout << X << " " << (X - (double)ext[e].x) << endl;
//cout << "@ " << ext[e] << "(" << e << ") // " << base[f] << ".." << base[f+1] << endl;

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
            e++;
        P = max(P, base[f].x - segment_at_y(ext[e], ext[e1], base[f].y));
    }



    cout << P << endl;

    for(uint32_t i = 0; i < n; i++)
        cout << base[i] << ", "; cout << endl;
    for(uint32_t i = 0; i < m; i++)
        cout << vec2d{ext[i].x+(int64_t)ceil(P), ext[i].y} << ", "; cout << endl;

    cout << "X" << endl;
    double minX = 0, maxX = 0;
    for(uint32_t i = 0; i < n; i++)
        minX = min(minX, (double)base[i].x), maxX = max(maxX, (double)base[i].x);
    cout << minX << " " << maxX << endl;
    for(uint32_t i = 0; i < m; i++)
        minX = min(minX, ext[i].x+P), maxX = max(maxX, ext[i].x+P);
    cout << minX << " " << maxX << endl;

    return maxX - minX;
}



int main()
{
    uint32_t n;
    cin >> n;
    cout << fixed << setprecision(3) << endl;
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
    {
        cout << "<< " << i << " -> " << j << " >>" << endl;
        max_overlap[i][j] = (width[i] + width[j]) - min_sticky(sheets[i], sheets[j]);
        cout << " === " << max_overlap[i][j] << " === " << endl << endl;
    }
    for(uint32_t i = 0; i < n; i++)
        for(uint32_t j = 0; j < n; j++)
            cout << i << " -> " << j << ": " << max_overlap[i][j] << endl;

    vector<uint32_t> P(n);
    iota(P.begin(), P.end(), 0);
    double result = numeric_limits<double>::max();
    do {
        double curr = width[P[0]];
        for(uint32_t i = 1; i < n; i++)
            curr += width[P[i]] - max_overlap[P[i-1]][P[i]];
        result = min(result, curr);
        if(result == curr)
            for(uint32_t i = 0; i < n; i++)
                cout << P[i] << " "; cout << endl;
    } while(next_permutation(P.begin(), P.end()));

    cout << result;
}
