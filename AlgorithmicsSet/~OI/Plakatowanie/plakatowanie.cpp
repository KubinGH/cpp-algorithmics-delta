#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    uint32_t r = 0;
    stack<uint32_t> P;
    P.push(0);
    for(uint32_t i = 0, _, h; i < n; i++)
    {
        cin >> _ >> h;
        while(P.top() > h)
            P.pop();
        if(P.top() < h)
            r++, P.push(h);
    }
    cout << r;
}
