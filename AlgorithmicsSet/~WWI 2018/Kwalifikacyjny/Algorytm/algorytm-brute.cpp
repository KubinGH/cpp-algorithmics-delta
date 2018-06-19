#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t a, b;
    cin >> a >> b;
    uint64_t r = 0;
    while(a != b)
    {
        if(a > b)
            swap(a, b);
        r++;
        b -= a;
    }
    cout << r;
}
