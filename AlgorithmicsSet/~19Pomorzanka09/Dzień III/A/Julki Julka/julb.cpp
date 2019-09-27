#include <bits/stdc++.h>

using namespace std;

const uint MOD = 1009;

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

    vector<uint> J(k+1), S(k+2);

    J[0] = 1;
    for(size_t i = 0, s = 0; i < m; i++)
    {
        s += A[i]; s = min(s, k);
        partial_sum(J.begin(), J.begin() + s, S.begin() + 1);
        for(size_t l = s+1; l --> A[i]; )
            J[l] += S[l] - S[l-A[i]], J[l] %= MOD;
        for(size_t l = A[i]; l --> 0; )
            J[l] += S[l], J[l] %= MOD;
    }

    cout << J[k];
}
