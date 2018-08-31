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
    set<uint32_t> S;
    uint32_t j = i - 1;
    while(j < A.size() and A[j] == A[i-1])
    {
        S.insert(G(A, j));
        j--;
    }
    return mex(S);
}
bool Gt(vector<bool>& A, uint32_t i)
{
    if(i == 0)
        return false;
    else if(i > 1 and A[i-2] == A[i-1])
        return true;
    else
        return not Gt(A, i-1);
}

int main()
{
    ios_base::sync_with_stdio(false);
    /*
    string S;
    cin >> S;
    reverse(S.begin(), S.end());
    vector<bool> A(S.size()); uint32_t n = S.size();
    for(uint32_t i = 0; i < n; i++) A[i] = S[i] == 'A';
    */
    uint32_t n = 12;
    vector<bool> A(n);
    for(uint32_t m = 0; m < (1 << n); m++)
    {
        for(uint32_t i = 0; i < n; i++)
            A[i] = m & (1 << i);
        cout << "X ";
        for(uint32_t i = 0; i < n; i++)
            cout << A[i] << " "; cout << "\n";
        for(uint32_t i = 0; i <= n; i++)
            cout << G(A, i) << " "; cout << "\n";
        for(uint32_t i = 0; i <= n; i++)
            cout << Gt(A, i) << " "; cout << "\n";
        for(uint32_t i = 0; i <= n; i++)
            assert((G(A, i) != 0) == Gt(A, i));
    }
}
