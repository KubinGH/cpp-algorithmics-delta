#include <bits/stdc++.h>

using namespace std;

const int64_t oo = INT64_MAX / 3;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, k; uint64_t m;
    cin >> n >> k >> m;

    vector<int64_t> P(n+2);
    P[0] = -oo; P[n+1] = +oo;

    for(size_t i = 1; i <= n; i++)
        cin >> P[i];

    vector<size_t> F(n+2, SIZE_MAX);

    for(size_t tr : {0, 1})
    {
        for(size_t i = 1; i <= n; i++)
        {
            size_t lo = max(0, int(k-i)), hi = min(n-i, k);
            while(lo < hi)
            {
                const auto l = (lo + hi) / 2;
                if(2*P[i] <= P[i-(k-l)] + P[i+l])
                    hi = l;
                else
                    lo = l+1;
            }
            if(P[i+lo] - P[i] >= P[i] - P[i - (k-lo)]
               and P[i+lo] - P[i] <= P[i] - P[i - (k-lo) - 1])
                F[i] = i+lo;
        }

        reverse(F.begin(), F.end());
        reverse(P.begin(), P.end());
        for(size_t i = 1; i <= n; i++)
            F[i] = n-F[i]+1;
        for(auto& x : P)
            x = -x;
    }

    vector<size_t> R(n+2);
    iota(R.begin(), R.end(), 0);
    vector<size_t> G = F;

    while(m)
    {
        if(m % 2)
            for(size_t i = 1; i <= n; i++)
                R[i] = F[R[i]];
        m /= 2;
        for(size_t i = 1; i <= n; i++)
            G[i] = F[F[i]];
        swap(F, G);
    }

    for(size_t i = 1; i <= n; i++)
        cout << R[i] << ' ';
    cout << endl;
}
