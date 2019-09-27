#include <bits/stdc++.h>

using namespace std;

const uint MOD = 1009;

vector<uint> W(size_t k, size_t a, uint u)
{
    if(u == 0)
    {
        vector<uint> r(k+1); r[0] = 1;
        return r;
    }
    else if(u % 2 == 1)
    {
        auto w = W(k, a, u - 1);
        vector<uint> s(k+2);
        partial_sum(w.begin(), w.end(), s.begin()+1);
        for(size_t l = k+1; l --> 0; )
            w[l] += s[l] - s[max(l, a)-a], w[l] %= MOD;
        return w;
    }
    else
    {
        auto v = W(k, a, u / 2);
        vector<uint> w(k+1);
        for(size_t l = 0; l <= k; l++)
        {
            size_t h = min({k, u*a, l});
            for(size_t i = 0; i <= h; i++)
                w[l] += v[i] * (i <= l ? v[l-i] : 0);
            w[l] %= MOD;
        }
        return w;
    }
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

        fill(J.begin(), J.end(), 0);
        for(size_t l = k+1; l --> 0; )
        {
            for(size_t c = 0; c <= min(k, u*A[i]); c++)
                if(c <= l)
                    J[l] += w[c] * J0[l - c];
            J[l] %= MOD;
        }

        swap(J, J0);
    }

    cout << J0[k];
}
