#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t n;
    cin >> n;
    while(n % 2 == 0)
        n /= 2, cout << "2 ";
    uint64_t b = ceil(sqrt(n)) + 2;
    for(uint64_t i = 2; i < b; i++)
    {
        while(n % i == 0)
            n /= i, cout << i << ' ';
    }
    if(n != 1)
        cout << n;
}
