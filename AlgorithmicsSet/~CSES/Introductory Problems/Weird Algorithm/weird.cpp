#include <bits/stdc++.h>

using namespace std;

int main()
{
    int64_t n;
    cin >> n;

    while(n != 1)
    {
        cout << n << endl;
        n = (n % 2 ? 3*n + 1 : n/2);
    }
    cout << "1" << endl;
}
