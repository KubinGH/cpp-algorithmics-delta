#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t d;
    cin >> d;

    uint X = 0;
    while(d --> 0)
    {
        uint x;
        cin >> x;
        X ^= x;
    }
    cout << X << endl;
}
