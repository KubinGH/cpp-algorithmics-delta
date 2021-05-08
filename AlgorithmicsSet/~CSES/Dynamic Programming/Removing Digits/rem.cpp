#include <bits/stdc++.h>

using namespace std;

int main()
{
    size_t n;
    cin >> n;

    vector<int> R(n+1, INT_MAX-0xD);
    R[0] = 0;
    for(size_t i = 1; i <= n; i++)
    {
        auto j = i;
        while(j)
            R[i] = min(R[i], R[i-j%10] + 1), j /= 10;
    }

    cout << R[n] << endl;
}
