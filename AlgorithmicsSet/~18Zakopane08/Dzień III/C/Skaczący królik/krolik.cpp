#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t n; uint32_t k;
    cin >> n >> k;
    uint32_t x = 0, y = 0;
    bool t = false;
    uint64_t p = 1, r = 1;
    for(uint32_t i = 0; i < k; i++)
    {
        char c;
        cin >> c;
        if(c == 'G')
        {
            y--;

        }
        else if(c == 'D')
        {
            y++;

        }
        else if(c == 'L')
        {
            x--;
        }
        else if(c == 'P')
        {
            x++;

        }
        t = not t;
    }
    cout << r;
}
