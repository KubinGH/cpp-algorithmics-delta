#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, g = 0;
    while(cin >> n)
    {
        if(n)
        {
            if(not g)
                g = n;
            else
                g = __gcd(g, n);
        }
    }
    if(g)   cout << g;
    else    cout << "BRAK";

}
