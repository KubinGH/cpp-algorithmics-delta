#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1u << 18;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static uint32_t H[MAX];
    for(uint32_t i = 0, _; i < n; i++)
        cin >> _ >> H[i];
    uint32_t r = 0;
    stack<uint32_t> P;
    P.push(0);
    for(uint32_t i = 0; i < n; i++)
    {
        while(P.top() > H[i])
            P.pop();
        if(P.top() < H[i])
        {
            r++;
            P.push(H[i]);
        }
    }
    cout << r;
}
