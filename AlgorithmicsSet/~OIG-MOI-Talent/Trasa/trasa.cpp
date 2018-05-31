#include <bits/stdc++.h>

using namespace std;

int main()
{
    uint32_t p, k;
    cin >> p >> k;
    // d = k + p%d
    // (100-p)/100 * d = k
    // d = k / ((100-p)/100)
    // d = 100k / (100-p)
    cout << 100*k / (100-p);
}
