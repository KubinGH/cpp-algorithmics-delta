#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 16;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t r = 0;
    for(uint32_t a = 0; a < 2; a++)
     for(uint32_t b = 0; b < 2; b++)
    {
        cout << a << " " << b << endl, r++;
    }
    cout << r << endl;
    r = 0;
    for(uint32_t a = 0; a < 3; a++)
     for(uint32_t b = 0; b < 3; b++)
      for(uint32_t c = 0; c < 3; c++)
    {
        if(a < c)
        //    cout << a << " " << b << " " << c << endl, r++;
            cout << max(a, b) << " " << max(b, c) << endl, r++;
    }
    cout << r << endl;
    r = 0;
    for(uint32_t a = 0; a < 4; a++)
     for(uint32_t b = 0; b < 4; b++)
      for(uint32_t c = 0; c < 4; c++)
       for(uint32_t d = 0; d < 4; d++)
    {
        if(a < c and a < d and b < d)
        //    cout << a << " " << b << " " << c << " " << d << endl, r++;
            cout << max(a, b) << " " << max(b, c) << " " << max(c, d) << endl, r++;
    }
    cout << r << endl;
    r = 0;
    for(uint32_t a = 0; a < 5; a++)
     for(uint32_t b = 0; b < 5; b++)
      for(uint32_t c = 0; c < 5; c++)
       for(uint32_t d = 0; d < 5; d++)
        for(uint32_t e = 0; e < 5; e++)
    {
        if(a < c and a < d and b < d and b < e and c < e)
        //    cout << a << " " << b << " " << c << " " << d << " " << e << endl, r++;
            cout << max(a, b) << " " << max(b, c) << " " << max(c, d) << " " << max(d, e) << endl, r++;
    }
    cout << r << endl;
    r = 0;
    return 0;
    for(uint32_t a = 0; a < 6; a++)
     for(uint32_t b = 0; b < 6; b++)
      for(uint32_t c = 0; c < 6; c++)
       for(uint32_t d = 0; d < 6; d++)
        for(uint32_t e = 0; e < 6; e++)
         for(uint32_t f = 0; f < 6; f++)
    {
        if(a < c and a < d and b < d and b < e and c < e and c < f and d < f)
            cout << a << " " << b << " " << c << " " << d << " " << e << " " << f << endl, r++;
    }
    cout << r << endl;
}
