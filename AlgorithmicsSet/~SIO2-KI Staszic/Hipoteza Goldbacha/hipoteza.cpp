#include <bits/stdc++.h>

using namespace std;

uint32_t is_prime(uint32_t x)
{
    for(uint32_t i = 2; i * i <= x; i++)
        if(x % i == 0)
            return false;
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t t;
    cin >> t;
    while(t --> 0)
    {
        uint32_t n;
        cin >> n;
        for(uint32_t p = n/2+1; p --> 0; )
        {
            if(is_prime(p) and is_prime(n-p))
            {
                cout << p << " " << n-p << "\n";
                break;
            }
        }
    }
}
