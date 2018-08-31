#include <bits/stdc++.h>

using namespace std;

uint32_t mex(set<uint32_t>& S)
{
    uint32_t i = 0;
    for(uint32_t x : S)
    {
        if(x != i)
            return i;
        i++;
    }
    return i;
}

uint32_t G(vector<bool>& A, uint32_t i)
{
    if(i == 0)
        return false;
    else if(i > 1 and A[i-2] == A[i-1])
        return true;
    else
        return not G(A, i-1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t t;
    cin >> t;
    while(t --> 0)
    {
        string S;
        cin >> S;
        reverse(S.begin(), S.end());
        vector<bool> A(S.size()); uint32_t n = S.size();
        for(uint32_t i = 0; i < n; i++) A[i] = S[i] == 'A';
        if(G(A, n) > 0)
            cout << "Ania\n";
        else
            cout << "Bogdan\n";
    }
}
