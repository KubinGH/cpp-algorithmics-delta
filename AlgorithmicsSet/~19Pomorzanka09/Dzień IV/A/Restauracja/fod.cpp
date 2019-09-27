#include <bits/stdc++.h>

using namespace std;

int main()
{
    size_t n, g, t;
    cin >> n >> g >> t;

    vector<uint> A(n);
    for(auto& a : A)
        cin >> a;
    sort(A.begin(), A.end());

    using ldouble = double;
    map<pair<size_t, size_t>, ldouble> cache;
    function<ldouble(size_t, size_t)> solve = [&](size_t mask, size_t visitors) {
        if(visitors == 0)
            return 0.;
        if(cache.count({mask, visitors}))
            return cache[{mask, visitors}];
        ldouble re = 0;
        size_t i = 0;
        for(uint x = 1; x <= g; x++)
        {
            while(i < n and ((mask>>i & 1) or A[i] < x))
                i++;
            if(i == n)
                re += solve(mask, visitors - 1);
            else
                re += x + solve(mask | (1 << i), visitors - 1);
        }
        return cache[{mask, visitors}] = re / g;
    };

    cout << fixed << setprecision(10) << solve(0, t);
}
