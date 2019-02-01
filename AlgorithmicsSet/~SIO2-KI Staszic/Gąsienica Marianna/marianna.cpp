#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    vector<uint32_t> A(n), S(n+1);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i], S[i+1] = S[i] + A[i];
    uint32_t c = 0, r = -1u;
    for(uint32_t i = 0, j = 1; j <= n; j++)
    {
        c += A[j-1];
        if(c > k)
            i++, c--;
        while(not A[i] and i < j) i++;
        if(c == k)
            r = min(r, j - i);
    }
    if(r == -1u)
        cout << "NIE";
    else
        cout << r - k;
}
