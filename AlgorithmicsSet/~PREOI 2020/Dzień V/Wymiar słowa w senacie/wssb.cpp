#include <bits/stdc++.h>

using namespace std;

int main()
{
    size_t n;
    cin >> n;

    string S;
    cin >> S;

    for(size_t m = 1; m <= n; m++)
    {
        auto it = mismatch(S.begin(), S.begin() + m, S.rbegin() + (n - m)).first;
        cout << (it - S.begin()) << ' ';
    }
}
