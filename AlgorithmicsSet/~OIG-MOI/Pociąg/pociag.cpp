#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> W, M, IM;
    for(uint32_t i = 0; i < n; i++)
        cin >> W[i];
    for(uint32_t i = 0; i < n; i++)
        cin >> M[i], IM[M[i]] = i;
    uint32_t b = IM[W[n-1]], r = 1;
    bool borrowed = false;
    for(uint32_t i = n - 1; i --> 0;)
    {
        uint32_t c = IM[W[i]];
        if(c < b)
            r++, borrowed = c == 0;
        else
            borrowed = false;
        b = c;
    }
    cout << r - borrowed;
}
