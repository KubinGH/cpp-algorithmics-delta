#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e6;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string S;
    cin >> S;
    uint32_t n = S.size();
    static array<uint32_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        A[i] = S[i] - 'a';
    static array<uint32_t, 64> R;
    uint32_t r = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        if(A[i] == 0)
            R[A[i]]++;
        else
            R[A[i]] = max(R[A[i]-1], R[A[i]]) + 1;
        r = max(R[A[i]], r);
    }
    cout << r;
}
