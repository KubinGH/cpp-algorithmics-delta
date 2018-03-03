#include <bits/stdc++.h>

using namespace std;

int main()
{
    uint32_t n, k;
    cin >> n >> k;
    if(n % k == 0)
        cout << '0';
    else
        cout << k - (n % k);
}
