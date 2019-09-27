#include <bits/stdc++.h>
#include <ext/numeric>
#include <ktl/math/fft.cpp>
#include <ktl/math/poly.cpp>
#include <ktl/util/extio.cpp>

using namespace std;

const int64_t MOD = 1009;

struct modd { int64_t operator() (int64_t x) { return x % MOD; } };
using mypoly = polynomial<int64_t, rfft<int64_t, double, 0>, modd>;

struct polysizecmp
{
    bool operator() (const mypoly& a, const mypoly& b)
    {
        return a.P.size() > b.P.size();
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, k;
    cin >> n >> m >> k;

    vector<size_t> A(m);
    for(size_t i = 0; i < n; i++)
    {
        size_t a;
        cin >> a; a--;
        A[a]++;
    }

    priority_queue<mypoly, vector<mypoly>, polysizecmp> Q;

    for(size_t i = 0; i < m; i++)
    {
        if(not A[i]) continue;
        mypoly p(min(A[i], k));
        fill(p.P.begin(), p.P.end(), 1);
        Q.push(p);
    }

    while(Q.size() > 1)
    {
        auto p = Q.top(); Q.pop();
        auto q = Q.top(); Q.pop();
        auto r = p * q;

        while(r.P.size() > k+1) r.P.pop_back();
        Q.push(r);
    }

    cout << Q.top().P[k];
}
