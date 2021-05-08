#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    int64_t m = n;
    map<int64_t, size_t> cnt = {{0, 1}};
    int64_t s = 0, r = 0;
    for(size_t i = 0; i < n; i++)
    {
        int64_t a;
        cin >> a;
        s += a; s %= m; s = (s < 0 ? s + m : s);
        r += cnt[s]++;
    }

    cout << r << endl;
}
