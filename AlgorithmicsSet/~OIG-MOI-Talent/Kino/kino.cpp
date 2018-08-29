#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n; string S;
    cin >> n >> S;
    vector<bool> H(S.size()+1);
    for(uint32_t i = 0; i < S.size(); i++)
        H[i] = i == 0 or S[i] == 'S' or S[i-1] == 'S' or (i >= 2 and S[i-1] == 'L' and S[i-2] == 'L' and H[i-2]);
    H[S.size()] = true;
    vector<bool> U(S.size()+1);
    uint32_t r = 0;
    for(uint32_t i = 0; i < S.size(); i++)
    {
        if(H[i] and not U[i])
            U[i] = true, r++;
        else if(H[i+1] and not U[i+1])
            U[i+1] = true, r++;
    }
    cout << r;
}
