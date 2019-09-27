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

    vector<uint> J(k+1), J0(k+1);
    J0[0] = 1;

    for(size_t i = 0; i < m; i++)
    {
        size_t u = 1;
        while(i+1 < m and A[i] == A[i+1])
            i++, u++;

        
    }

    cout << J[k];
}
