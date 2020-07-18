#include <bits/stdc++.h>

using namespace std;

int64_t find_shortcut(int _n, vector<int> L, vector<int> D, int c)
{
    size_t n = _n;
    vector<int64_t> X(n);
    for(size_t i = 1; i < n; i++)
        X[i] = X[i-1] + L[i-1];

    int64_t lo = 0, hi = accumulate(L.begin(), L.end(), (int64_t)0) + accumulate(D.begin(), D.end(), (int64_t)0);
    while(lo < hi)
    {
        int64_t k = (lo + hi) / 2;

        int64_t u1 = INT64_MIN, u2 = INT64_MAX, v1 = INT64_MIN, v2 = INT64_MAX;
        // This code actually finds solutions to a set of inequalities by treating
        // them geometrically as a set of squares rotated by 45 deg, first by rotating
        // them and then intersecting them ([u1..u2] x [v1..v2])
        // opt: Add two segment/Fenwick trees for min/max queries for D[j]-X[j]/D[j]+X[j] or similar
        // indexed by D[j]-X[j], in order to omit j not satysfying condition after fixing i
        // some scaling may be necessary. Achieves O(n log n)
        for(size_t i = 0; i < n; i++)
          for(size_t j = 0; j < i; j++)
        {
            if(D[i] + D[j] + X[i] - X[j] > k)
            {
                int64_t p = X[i], q = X[j], r = k - c - D[i] - D[j];
                u1 = max(u1, p + q - r);
                u2 = min(u2, p + q + r);
                v1 = max(v1, p - q - r);
                v2 = min(v2, p - q + r);
            }
        }

        bool ok = false;
        // opt: Replace with some simple searches for b after fixing a for O(n log n)
        for(size_t a = 0; a < n; a++)
          for(size_t b = 0; b < a; b++)
            if(u1 <= X[a]+X[b] and X[a]+X[b] <= u2 and v1 <= X[a]-X[b] and X[a]-X[b] <= v2)
                ok = true;

        if(ok)
            hi = k;
        else
            lo = k + 1;
    }

    return lo;
}
