#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t n;
    cin >> n;
    static array<uint64_t, MAX> A, D;
    static array<uint64_t, 2*(MAX+1)> S;
    for(uint64_t i = 0; i < n; i++)
        cin >> A[i] >> D[i], S[i+1] = S[i] + D[i];
    for(uint64_t i = n; i < 2*n; i++)
        S[i+1] = S[i] + D[i-n];
    for(uint64_t i = 0; i < n; i++)
    {
        A[i] %= S[n];
        auto it = upper_bound(S.begin(), S.begin() + 2*n+1, A[i] + S[i]);
        uint64_t d = distance(S.begin(), it) - 1;
        cout << (d % n) + 1 << '\n';
    }
}
