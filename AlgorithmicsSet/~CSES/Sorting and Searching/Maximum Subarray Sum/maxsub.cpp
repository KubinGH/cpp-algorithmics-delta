#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    int64_t best[2] = {INT64_MIN, INT64_MIN};
    while(n --> 0)
    {
        int a;
        cin >> a;
        best[0] = max(best[0], best[1] = max(best[1], 0l) + a);
    }

    cout << best[0] << endl;
}
