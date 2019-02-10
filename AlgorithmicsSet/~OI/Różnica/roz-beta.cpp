#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n; string S;
    cin >> n >> S;
    int32_t result = 0;
    for(char master = 'a'; master <= 'z'; master++)
      for(char slave = 'a'; slave <= 'z'; slave++)
        if(master != slave)
    {
        int32_t curr = 0, best = 0;
        bool any_slave = false;
        for(uint32_t i = 0; i < n; i++)
        {
            int32_t v = (S[i] == master ? 1 : (S[i] == slave ? -1 : 0));
            if(v == -1)
                curr = max(curr, 0), any_slave = true;
            curr = curr + v;
            best = max(best, curr);
        }
        if(any_slave) result = max(result, best);
    }
    cout << result;
}
