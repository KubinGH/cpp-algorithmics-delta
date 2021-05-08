#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t k, m;
    cin >> k >> m;

    vector<uint> cnt(k);
    for(size_t i = 0; i < k; i++)
    {
        uint a;
        cin >> a;
        cnt[a]++;
    }
    auto mv = [&](uint x, uint y) {
        const auto c = cnt[x];
        cnt[x] -= c; cnt[y] += c;
    };
    while(m --> 0)
    {
        uint x, p;
        cin >> x >> p;
        const auto y = k - x - 1;
        const auto c = min(cnt[x], cnt[y]);
        cnt[x] -= c; cnt[y] -= c;
        mv(x, x*p % k); mv(y, y*p % k);
    }
    cout << accumulate(cnt.begin(), cnt.end(), 0) << endl;
}
