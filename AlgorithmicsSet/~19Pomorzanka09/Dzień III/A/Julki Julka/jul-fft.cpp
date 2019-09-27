#include <bits/stdc++.h>
#include <ext/numeric>
#include <ktl/math/fft.cpp>
#include <ktl/math/poly.cpp>
#include <ktl/util/extio.cpp>

using namespace std;

const uint MOD = 1009;

struct modd { uint operator() (uint x) { return x % MOD; } };
using mypoly = polynomial<uint, rfft<uint, double>, modd>;
using mypolymul = poly_multiplies<uint, rfft<uint, double>>;

mypoly W(size_t k, size_t a, uint u)
{
    mypoly p(k+1);
    fill(p.P.begin(), p.P.begin() + min(k+1, a+1), 1);
    auto r = power(p, u);
    while(r.P.size() > k) r.P.pop_back();
    return r;
}

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
    sort(A.rbegin(), A.rend());
    while(not A.back()) A.pop_back();
    reverse(A.begin(), A.end());

    vector<uint> J(k+1), J0(k+1);
    J0[0] = 1;

    for(size_t i = 0; i < m; i++)
    {
        size_t u = 1;
        while(i+1 < m and A[i] == A[i+1])
            i++, u++;
        auto w = W(k, A[i], u);
        mypoly p(J0);
        J = (w * p).P;
        swap(J, J0);
    }

    cout << J0[k];
}
