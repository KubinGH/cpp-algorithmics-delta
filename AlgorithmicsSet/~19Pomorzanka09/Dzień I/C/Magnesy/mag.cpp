#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, l;
    cin >> n >> l;

    vector<int> A;
    A.reserve(n);

    char la = '0';
    for(size_t i = 0; i < n; i++)
    {
        char a, b;
        cin >> a >> b;
        if(a == la) A.back()++;
        else A.push_back(1);
        la = a;
    }

    size_t result = SIZE_MAX;
    auto try_solve = [&](size_t i0 = 0) {
        size_t m = A.size();
        vector<int> S(m + 1);
        partial_sum(A.begin(), A.end(), S.begin() + 1);

        vector<size_t> I(n+l+1, SIZE_MAX);
        for(size_t i = 0; i <= m; i++)
            I[S[i]] = i;
        I[0] = i0;

        for(size_t i = 0; i < m; i++)
            if(S[i]+l <= n and I[S[i]+l] != SIZE_MAX and (I[S[i]+l]-i) % 2)
                result = min(result, (I[S[i]+l] - i) / 2);
    };

    try_solve();
    A.push_back(0);
    try_solve();
    A.pop_back();
    A.insert(A.begin(), 0);
    try_solve(1);

    cout << result << endl;
}
