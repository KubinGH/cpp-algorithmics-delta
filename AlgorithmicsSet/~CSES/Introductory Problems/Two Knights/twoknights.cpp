#include <bits/stdc++.h>

using namespace std;

__extension__ using int128_t = __int128;

int64_t f(int64_t n)
{
    return (-16 + n*(24 + n*(-9 + n*n))) / 2;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    for(size_t k = 1; k <= n; k++)
        cout << f(k) << '\n';
    cout << endl;
}
