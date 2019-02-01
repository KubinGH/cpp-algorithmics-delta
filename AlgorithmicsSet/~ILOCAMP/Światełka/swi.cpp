#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n; int32_t k;
    cin >> n >> k;
    vector<int32_t> A(n+1); A[0] = 0;
    for(uint32_t i = 1; i <= n; i++)
        cin >> A[i];
    vector<bool> B(n+1); B[0] = 1;
    for(uint32_t i = 1; i <= n; i++)
    {
        bool b; cin >> b;
        B[i] = b;
    }
    uint32_t next_todo = 1, last_mid;
    auto push_todo = [&](uint32_t mid) {
        last_mid = mid;
        while(next_todo < n and A[next_todo] - A[mid] <= k)
            next_todo++;
        if(A[next_todo] - A[mid] > k) next_todo--;
    };
    push_todo(0);
    uint32_t result = 0;
    for(uint32_t i = 1; i <= n; i++)
    {
        if(i == n and i == next_todo and A[i] - A[last_mid] <= k)
            break;
        if(i == next_todo or B[i])
            result += not B[i], push_todo(i);
    }
    cout << result;
}
