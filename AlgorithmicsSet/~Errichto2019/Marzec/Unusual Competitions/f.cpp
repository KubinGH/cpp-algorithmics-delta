#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    string S;
    cin >> S;

    int r = 0, s = 0;
    for(size_t i = 0; i < n; i++)
    {
        auto z = s + (S[i] == '(' ? 1 : -1);
        r += (s < 0 or z < 0);
        s = z;
    }

    cout << (s ? -1 : r);
}
