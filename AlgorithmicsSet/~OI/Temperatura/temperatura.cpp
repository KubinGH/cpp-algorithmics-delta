#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 20, MAX_A = 1 << 7;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static int32_t A[MAX], B[MAX];
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i] >> B[i];
    deque<pair<int32_t, uint32_t>> P;
    uint32_t r = 0, c = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t o = 1;
        while(not P.empty() and P.front().first < A[i])
            o += P.front().second, P.pop_front();
        P.emplace_front(A[i], o); c++;
        while(not P.empty() and P.back().first > B[i])
            c -= P.back().second, P.pop_back();
        r = max(r, c);
    }
    cout << r;
}
