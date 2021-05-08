#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    int64_t result = 0;
    int last = 0, curr;
    while(n --> 0)
    {
        cin >> curr;
        result += max(0, last - curr);
        last = max(last, curr);
    }

    cout << result << endl;
}
