#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n; uint64_t k;
    cin >> n >> k; k -= n;
    static array<long double, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    priority_queue<pair<long double, uint32_t>> Q;
    static array<long double, MAX> B;
    static array<uint32_t, MAX> W;
    for(uint32_t i = 0; i < n; i++)
        Q.emplace(A[i], i), W[i] = 1, B[i] = A[i];
    for(uint32_t ki = 0; ki < k; ki++)
    {
        auto p = Q.top(); Q.pop();
        uint32_t i = p.second;
        long double g = A[i]/W[i] - A[i]/(W[i]+1);
        B[i] -= g;
        W[i]++;
        Q.emplace(B[i], i);
    }
    cout << fixed << *max_element(B.begin(), B.begin() + n);
}
