#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e6;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, s, k;
    cin >> n >> s >> k;
    static uint32_t A[MAX];
    uint32_t result = 0, u = 0;
    uint32_t tbegin = 0;
    for(uint32_t tend = 1; tend <= n; tend++)
    {
        cin >> A[tend-1];
        u += A[tend-1];
        while(tbegin < tend and u + (tend-tbegin-1) * k > s)
            u -= A[tbegin], tbegin++;
        result = max(tend - tbegin, result);
    }
    cout << result;
}
