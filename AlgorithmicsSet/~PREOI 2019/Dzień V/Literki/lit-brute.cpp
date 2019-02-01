#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string S;
    uint32_t k;
    cin >> S >> k;
    const uint32_t n = S.size();
    uint32_t best_length = -1u, best_begin = -1u;
    for(uint32_t a = 0; a < n; a++)
      for(uint32_t b = a+1; b <= n; b++)
    {
        uint32_t cnt[26] = {0}, cnt_unique = 0;
        for(uint32_t i = a; i < b; i++)
            cnt[S[i] - 'a']++;
        for(uint32_t c = 0; c < 26; c++)
            if(cnt[c]) cnt_unique++;
        if(cnt_unique >= k)
        {
            if(b - a < best_length)
                best_length = b - a, best_begin = -1u;
            if(best_length == b - a)
                best_begin = min(best_begin, a);
        }
    }
    if(best_length == -1u)
        cout << "BRAK";
    else
        cout << best_begin+1 << " " << best_begin+best_length;
}
