#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 50000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint16_t n;
    int32_t e;
    cin >> n >> e;
    static array<int32_t, MAX> A;
    for(uint16_t i = 0; i < n; i++)
        cin >> A[i];
    sort(A.begin(), A.begin() + n);
    deque<int32_t> Q;
    Q.push_back(A[0]);
    int32_t m = A[0] - e;
    uint32_t ms = 1;
    for(uint16_t i = 1; i < n; i++)
    {
        int32_t c = A[i];
        while(not Q.empty() and c - Q.front() > 2 * e)
            Q.pop_front();
        Q.push_back(c);
        if(Q.size() > ms)
        {
            m = min(Q.front() + e, Q.back() - e);
            ms = Q.size();
        }
    }
    cout << m << " " << ms;
}
