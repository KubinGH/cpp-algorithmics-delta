#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    for(uint32_t i = 1; i <= n+1; i++)
    {
        if(n % i == 0 and n % (i+1) != 0)
        {
            cout << i;
            return 0;
        }
    }
}
