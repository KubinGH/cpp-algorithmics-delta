#include <bits/stdc++.h>

using namespace std;

vector<uint32_t> prefixoprefixes(const string& S)
{
    const uint32_t n = S.size();
    vector<uint32_t> Z(n);
    uint32_t L = 0, R = 0;
    Z[0] = n;
    for(uint32_t i = 1; i < n; i++)
    {
        if(i <= R and Z[i-L] < R-i+1)
            Z[i] = Z[i-L];
        else
        {
            L = i;
            if(i > R) R = i;
            while(R < n and S[R-L] == S[R])
                R++;
            R--;
            Z[i] = R-L+1;
        }
    }
    return Z;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string U, V;
    cin >> U >> V;
    reverse(U.begin(), U.end());
    reverse(V.begin(), V.end());
    string S = U + "#" + V;
    auto Z = prefixoprefixes(S);
    vector<uint32_t> R(U.size()+1);
    for(uint32_t i = U.size()+1; i < S.size(); i++)
        R[Z[i]]++;
    vector<uint32_t> W(U.size()+1);
    partial_sum(R.rbegin(), R.rend(), W.rbegin());
    for(uint32_t i = 1; i <= U.size(); i++)
        cout << W[i] << " ";
}
