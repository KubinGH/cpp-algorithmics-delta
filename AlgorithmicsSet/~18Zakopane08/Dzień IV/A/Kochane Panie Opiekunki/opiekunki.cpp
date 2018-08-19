#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e5 + 16;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t p, n, jump; uint64_t per;
    cin >> p >> n >> jump >> per;
    static uint64_t A[MAX], S[MAX+1];
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    partial_sum(A, A + n, S + 1);
    auto sum = [&](uint32_t i, uint32_t j) { return S[j+1] - S[i]; };
    uint32_t rx = 0, r = 0;
    uint32_t hi = p == 1 ? n : (n+1)/2;
    bool done_two = false;
solver:
    uint32_t slaves = 0;
    for(uint32_t i = 0; i < hi; i++)
    {
        uint32_t come_before = (i == 0) ? -1u : min(n - 1, i - 1 + jump * i);
        uint32_t come_now = min(n - 1, i + jump * (i + 1));
        slaves += S[come_now+1] - S[come_before+1];
        //cout << i << ": " << slaves << endl;
        if(slaves >= per)
            slaves -= per;
        else
            r++;
    }
    if(p == 2 and not done_two)
    {
        reverse(A, A + n);
        partial_sum(A, A + n, S + 1);
        done_two = true;
        hi = n/2;
        rx = r;
        r = 0;
        goto solver;
    }
    //cout << rx << " " << r << endl;
    cout << max(rx, r);
}
