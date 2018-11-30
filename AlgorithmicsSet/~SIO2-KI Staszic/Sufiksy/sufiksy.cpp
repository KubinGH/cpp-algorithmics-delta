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
            Z[i] = R - L + 1;
        }
    }
    return Z;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string pattern, text;
    cin >> pattern >> text;
    reverse(pattern.begin(), pattern.end());
    reverse(text.begin(), text.end());
    auto Z = prefixoprefixes(pattern + "#" + text);
    vector<uint32_t> R(pattern.size()+1);
    for(uint32_t i = pattern.size()+1; i < Z.size(); i++)
        R[Z[i]]++;
    vector<uint32_t> S(pattern.size()+1);
    partial_sum(R.rbegin(), R.rend(), R.rbegin());
    for(uint32_t d = 1; d <= pattern.size(); d++)
        cout << R[d] << " ";
}
