#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    size_t n;
    cin >> n;

    int64_t result = 0;
    for(size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        if(i == 1) x = -x;
        else if(i > 1) x = abs(x);
        result += x;
    }

    cout << result;
}
