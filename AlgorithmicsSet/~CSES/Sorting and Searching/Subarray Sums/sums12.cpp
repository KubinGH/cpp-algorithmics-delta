#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n; int64_t x;
    cin >> n >> x;

    map<int64_t, size_t> cnt = {{0, 1}};
    int64_t s = 0, r = 0;
    while(n --> 0)
    {
        int64_t a;
        cin >> a;
        s += a;
        r += cnt[s - x];
        cnt[s]++;
    }

    cout << r << endl;
}
