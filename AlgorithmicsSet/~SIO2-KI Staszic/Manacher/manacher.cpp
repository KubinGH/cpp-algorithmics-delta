#include <bits/stdc++.h>

using namespace std;

vector<uint32_t> manacher(const string& So, char leaf = '#')
{
    size_t n = So.size();
    vector<char> S(2*n+1);
    for(size_t i = 0; i < n; i++)
        S[2*i] = leaf, S[2*i+1] = So[i];
    S[2*n] = leaf;
    n = 2*n + 1;
    vector<size_t> R(n);
    size_t m = 0;
    for(size_t i = 1; i < n; i++)
    {
        if(i < 2*m and i < m+R[m])
            R[i] = min(R[2*m - i], m+R[m] - i);
        while(i > R[i] and i+R[i] < n-1 and S[i-R[i]-1] == S[i+R[i]+1])
            R[i]++;
        if(i + R[i] > m + R[m])
            m = i;
    }
    for(uint32_t i = 0; i < n; i++)
        R[i] = (R[i]+1) / 2;
    return R;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    string S;
    cin >> S;
    auto radi = manacher(S);
    for(uint32_t i = 1; i < 2*n+1; i += 2)
        cout << radi[i] << " "; cout << "\n";
    for(uint32_t i = 2; i < 2*n; i += 2)
        cout << radi[i] << " "; cout << "\n";
}
