#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    int64_t s = (int64_t) n * (n + 1) / 2;
    for(size_t i = 1; i < n; i++)
    {
        int x;
        cin >> x;
        s -= x;
    }

    cout << s << endl;
}
