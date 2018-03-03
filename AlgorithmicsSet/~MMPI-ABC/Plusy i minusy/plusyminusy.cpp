#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 200000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<bool, MAX> A;
    static array<int32_t, MAX+1> S;
    for(uint32_t i = 0; i < n; i++)
    {
        char c;
        cin >> c;
        A[i] = c == '+';
        S[i+1] = S[i] + (A[i] ? 1 : -2);
    }
    static map<int32_t, uint64_t> C;
    C[0]++;
    uint64_t r = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        r += C[S[i+1]];
        C[S[i+1]]++;
    }
    cout << r;
}
