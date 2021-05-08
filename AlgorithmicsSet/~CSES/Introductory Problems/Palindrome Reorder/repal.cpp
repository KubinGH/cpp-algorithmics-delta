#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    string S;
    cin >> S;

    array<size_t, 256> cnt = {};
    for(auto c : S)
        cnt[c]++;

    size_t o = 0; uint8_t oi = 0;
    for(size_t c = 0; c < 256; c++)
        if(cnt[c] % 2)
            o++, oi = c;

    if(o > 1)
    {
        cout << "NO SOLUTION" << endl;
        return 0;
    }

    for(size_t c = 0; c < 256; c++)
        for(size_t r = 0; r < cnt[c] / 2; r++)
            cout << (uint8_t)c;
    if(o)
        cout << oi;
    for(size_t c = 256; c --> 0; )
        for(size_t r = 0; r < cnt[c] / 2; r++)
            cout << (uint8_t)c;
}
