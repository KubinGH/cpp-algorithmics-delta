#include <bits/stdc++.h>

using namespace std;

vector<size_t> prefixoprefixes(const string& S)
{
    const size_t n = S.size();
    vector<size_t> Z(n);

    for(size_t i = 1, L = 0, R = 0; i < n; i++)
    {
        if(i < R)
            Z[i] = min(R - i, Z[i - L]);
        while(i + Z[i] < n and S[Z[i]] == S[Z[i] + i])
            Z[i]++;
        if(i + Z[i] > R)
            L = i, R = i + Z[i];
    }

    return Z;
}


int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    string S;
    S.reserve(n);
    cin >> S;

    S.resize(2*n + 1, '#');
    for(size_t i = n+1; i <= 2*n; i++)
        S[i] = S[2*n-i];

    auto Z = prefixoprefixes(S);
    for(size_t i = 0; i < n; i++)
        cout << Z[2*n - i] << ' ';
}
