#include <bits/stdc++.h>

using namespace std;

vector<size_t> prefixoprefixes(string S)
{
    const size_t n = S.size();
    vector<size_t> Z(n);
    for(size_t i = 1, p = 0; i < n; i++)
    {
        if(i <= p + Z[p])
            Z[i] = min(Z[i - p], p + Z[p] - i);
        while(i + Z[i] < n and S[Z[i]] == S[i+Z[i]])
            Z[i]++;
        if(i + Z[i] > p + Z[p])
            p = i;
    }
    return Z;
}

bool square_insert(string S)
{
    auto P = prefixoprefixes(S);
    auto Q = prefixoprefixes(string(S.rbegin(), S.rend()));
    reverse(Q.begin(), Q.end());
    const size_t n = S.size() / 2;
    for(size_t i = 0; i <= n; i++)
        if(P[n+1] >= i and Q[n] >= n - i)
            return true;
    return false;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    string S;
    cin >> S;

    if(n % 2 == 0)
    {
        cout << "NOT POSSIBLE" << endl;
        return 0;
    }

    auto l = square_insert(S), r = square_insert(string(S.rbegin(), S.rend()));
    auto L = S.substr(S.size()/2 + 1, S.size()/2), R = S.substr(0, S.size()/2);

    if(l and r and L != R)
        cout << "NOT UNIQUE" << endl;
    else if(l)
        cout << L << endl;
    else if(r)
        cout << R << endl;
    else
        cout << "NOT POSSIBLE" << endl;
}
