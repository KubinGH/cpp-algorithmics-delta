#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    char curr, last = 0;
    size_t cnt = 0, result = 0;

    while(cin >> curr)
    {
        if(curr != last)
            last = curr, cnt = 0;
        result = max(result, ++cnt);
    }

    cout << result << endl;
}
