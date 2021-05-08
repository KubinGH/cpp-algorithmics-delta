#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    if(n <= 3)
    {
        cout << (n == 1 ? "1" : "NO SOLUTION") << endl;
        return 0;
    }

    for(size_t k = 2; k <= n; k += 2)
        cout << k << " ";
    for(size_t k = 1; k <= n; k += 2)
        cout << k << " ";
    cout << endl;
}
