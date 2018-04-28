#include <bits/stdc++.h>

using namespace std;

int main()
{
    int w, a, b, c = 1, r = 1;
    cin >> w >> w >> b;
    while(cin >> a)
    {
        if(a - b > w)
            c = 0;
        b = a;
        c++;
        r = max(r, c);
    }
    cout << r;
}
