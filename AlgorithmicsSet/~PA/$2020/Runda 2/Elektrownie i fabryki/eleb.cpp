#include <bits/stdc++.h>

using namespace std;

const int oo = INT_MAX/3;

int main()
{
    size_t n;
    cin >> n;

    vector<int64_t> A(n), S(n+1);
    for(size_t i = 0; i < n; i++)
        cin >> A[i], S[i+1] = S[i] + A[i];

    vector<int> R(n+1, -oo); R[n] = 0;
    map<int64_t, size_t> K = {{S[n], n}};
    for(size_t i = n; i --> 0; )
    {
        for(auto it = K.lower_bound(S[i]); it != K.end(); ++it)
            R[i] = max(R[i], R[it->second] + 1);

        if(R[i] >= 0)
            K[S[i]] = i;
    }

    cout << (R[0] >= 0 ? (int)n - R[0] : -1) << '\n';
}
