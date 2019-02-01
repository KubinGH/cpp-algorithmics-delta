#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

struct point { int32_t x, y, z; };
bool operator< (const point& lhs, const point& rhs)
{
    if(lhs.x == rhs.x)
    {
        if(lhs.y == rhs.y)  return lhs.z < rhs.z;
        else                return lhs.y < rhs.y;
    }
    else                    return lhs.x < rhs.x;
}

struct segment_tree
{
    uint32_t w;
    vector<uint32_t> values;
    segment_tree(uint32_t n)
    {
        w = 1 << __lg(2*n-1);
        values.resize(2*w, -1u);
    }
    void set(uint32_t p, uint32_t v)
    {
        p += w;
        if(values[p] < v) return;
        values[p] = v;
        while(p > 1)
            p /= 2, values[p] = min(values[2*p], values[2*p+1]);
    }
    uint32_t get(uint32_t getL, uint32_t getR)
    {
        uint32_t r = -1u;
        for(getL += w, getR += w+1; getL < getR; getL /= 2, getR /= 2)
        {
            if(getL % 2) r = min(r, values[getL++]);
            if(getR % 2) r = min(r, values[--getR]);
        }
        return r;
    }
};


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cerr.tie(0);
    uint32_t n;
    cin >> n;
    vector<point> P(n);
    vector<int32_t> Cx, Cy, Cz;
    Cx.reserve(n); Cy.reserve(n); Cz.reserve(n);
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> P[i].x >> P[i].y >> P[i].z;
        Cx.push_back(P[i].x); Cy.push_back(P[i].y); Cz.push_back(P[i].z);
    }
    #define MAKE_UNIQUE(_C) sort(_C.begin(), _C.end()); _C.erase(unique(_C.begin(), _C.end()), _C.end());
    MAKE_UNIQUE(Cx); MAKE_UNIQUE(Cy); MAKE_UNIQUE(Cz);
    gp_hash_table<int32_t, int32_t> Tx, Ty, Tz;
    #define MAKE_TRANS(_C, _T) for(uint32_t i = 0; i < _C.size(); i++) _T[_C[i]] = i;
    MAKE_TRANS(Cx, Tx); MAKE_TRANS(Cy, Ty); MAKE_TRANS(Cz, Tz);
    for(uint32_t i = 0; i < n; i++)
        P[i] = {Tx[P[i].x], Ty[P[i].y], Tz[P[i].z]};

    using pointdex = pair<point, uint32_t>;
    vector<pointdex> Pi(n);
    for(uint32_t i = 0; i < n; i++)
        Pi[i] = {P[i], i};
    sort(Pi.begin(), Pi.end());

    segment_tree T(n);
    vector<uint32_t> R; R.reserve(n);
    for(uint32_t i = 0; i < n; )
    {
        vector<pointdex> X;
        do {
            X.push_back(Pi[i++]);
        } while(i < n and X.back().first.x == Pi[i].first.x);

        sort(X.begin(), X.end());
        for(uint32_t j = 0; j < X.size(); )
        {
            vector<pointdex> Y;
            do {
                Y.push_back(X[j++]);
            } while(j < X.size() and Y.back().first.y == X[j].first.y);
            for(auto pi : Y)
                if(not pi.first.z or T.get(0, pi.first.z-1) >= (uint32_t)pi.first.y)
                    R.push_back(pi.second);
        }
        for(auto pi : X)
            T.set(pi.first.z, pi.first.y);
    }

    sort(R.begin(), R.end());
    cout << R.size() << "\n";
    for(uint32_t i : R)
        cout << i+1 << " ";
}
