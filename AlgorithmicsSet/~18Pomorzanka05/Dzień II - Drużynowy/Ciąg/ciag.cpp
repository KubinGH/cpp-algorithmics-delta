#include <bits/stdc++.h>

using namespace std;

int main()
{
    uint32_t t;
    cin >> t;
    for(uint32_t i = 0; i < t; i++)
    {
        uint32_t x, y;
        cin >> x >> y;
        uint32_t r = 0;
        if(x - y < 10)
        {
            for(uint32_t a = x; a <= y; a++)
                r += 2 - a%2;
            cout << r << "\n";
        }
        else
        {
            if(x%2 == 0)
                x++, r += 2;
            if(y%2 == 1)
                y--, r += 1;
            r += 3*((y-x+1)/2);
            cout << r << "\n";
        }
    }
}
