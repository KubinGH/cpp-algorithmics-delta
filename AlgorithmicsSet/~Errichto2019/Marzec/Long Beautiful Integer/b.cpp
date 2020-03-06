#include <bits/stdc++.h>

using namespace std;

string solve(string S, size_t k)
{
    const size_t n = S.size();

    vector<bool> K(n+1, true);
    for(size_t i = k+1; i <= n; i++)
        K[i] = K[i-1] and S[i-1] == S[(i-1)%k];

    string Z;

    for(size_t p = n+1; p --> k; )
    {
        if(K[p])
        {
            if(p < n and S[p%k] < S[p])
                break;

            Z.resize(n, '?');
            copy(S.begin(), S.begin() + p, Z.begin());
            for(size_t i = k; i < n; i++)
                Z[i] = Z[i-k];

            return Z;
        }
    }
    for(size_t p = k; p --> 0; )
    {
        if(S[p] != '9')
        {
            Z.resize(n, '?');
            copy(S.begin(), S.begin() + p, Z.begin());
            Z[p] = S[p] + 1;
            for(size_t i = p+1; i < k; i++)
                Z[i] = '0';
            for(size_t i = k; i < n; i++)
                Z[i] = Z[i-k];

            return Z;
        }
    }

    Z.resize(n+1, '0');
    for(size_t i = 0; i < n+1; i += k)
        Z[i] = '1';
    return Z;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, k;
    cin >> n >> k;

    string S;
    cin >> S;

    auto Z = solve(S, k);
    cout << Z.size() << endl;
    cout << Z << endl;
}
