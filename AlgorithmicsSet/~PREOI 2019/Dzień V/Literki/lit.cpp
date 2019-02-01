#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string S;
    cin >> S;
    uint32_t k;
    cin >> k;
    uint32_t cnt[26] = {0}, cnt_unique = 0;
    auto push = [&](char c) {
        if(++cnt[c - 'a'] == 1)
            cnt_unique++;
    };
    auto pop = [&](char c) {
        if(--cnt[c - 'a'] == 0)
            cnt_unique--;
    };
    const uint32_t n = S.size();
    uint32_t res_begin = -1u, res_length = -1u;
    for(uint32_t i = 0, j = 1; j <= n; j++)
    {
        push(S[j-1]);
        while(i < j and cnt_unique >= k)
            pop(S[i++]);
        if(i) push(S[--i]);
        if(cnt_unique >= k and j - i < res_length)
            res_begin = i, res_length = j - i;
    }
    if(res_length != -1u)
        cout << res_begin+1 << " " << res_begin + res_length;
    else
        cout << "BRAK";
}
