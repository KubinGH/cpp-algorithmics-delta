#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;
typedef int int32_t;

int main()
{
    uint32_t n;
    cin >> n;
    for(uint32_t i = 0; i < n; i++)
    {
        int32_t xa, ya, xb, yb, xc, yc;
        cin >> xa >> ya >> xb >> yb >> xc >> yc;
        int32_t xd = xa, yd = ya;
        xd += xc - xb;
        yd += yc - yb;
        if((yc - yb) * (xb - xa) == (yb - ya) * (xc - xb))
            cout << "NIE" << endl;
        else
            cout << xd << " " << yd << endl;
    }
}
