#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    size_t result = 0;
    unordered_set<int> seen;
    seen.reserve(4 * n);

    while(n --> 0)
    {
        int x;
        cin >> x;

        seen.insert(x);
        result += not seen.count(x - 1);
    }

    cout << result << endl;
}
