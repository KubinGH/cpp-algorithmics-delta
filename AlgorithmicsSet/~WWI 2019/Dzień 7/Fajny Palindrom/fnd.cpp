#include <bits/stdc++.h>

using namespace std;

bool odd_dig(uint n)
{
    while(n)
    {
        if((n % 10) % 2 == 0)
            return false;
        n /= 10;
    }
    return true;
}

bool is_pal(uint n)
{
    static char buf[16];
    size_t k = 0;
    while(n)
        buf[k++] = n % 10, n /= 10;
    for(size_t i = 0; i < k/2; i++)
        if(buf[i] != buf[k-i-1])
            return false;
    return true;
}

int main()
{
    uint x;
    cin >> x;

    for(size_t y = 1; y < x; y++)
    {
        cout << y << ": " << flush;
        for(uint n = 0; n < (1 << 26); n++)
        {
            if(n % x == y and odd_dig(n) and is_pal(n))
                cout << n << ", " << flush;
        }
        cout << endl;
    }

}
