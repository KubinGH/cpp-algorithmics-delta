#include <bits/stdc++.h>

using namespace std;

int f(int n, int k)
{
    if(n == 1)
        return 0;
    else if(2*k + 1 < n)
        return 2*k + 1;
    auto m = (n + 1) / 2, i = f(m, k - (n-m));
    return 2 * ((i + m - n%2) % m);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t q;
    cin >> q;

    while(q --> 0)
    {
        int n, k;
        cin >> n >> k;
        cout << 1 + f(n, k - 1) << '\n';
    }
}
