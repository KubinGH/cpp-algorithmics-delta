#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t w, h, q;
    cin >> w >> h >> q;
    vector<pair<uint32_t, uint32_t>> Q(q);
    for(uint32_t i = 0; i < q; i++)
        cin >> Q[i].first, Q[i].second = i;
    sort(Q.begin(), Q.end());

    vector<uint64_t> R(q);
    uint32_t t = 0;
    auto F = [&](uint32_t p, uint32_t r) {
        p = min(p, w-1); r = min(r, h-1);
        return uint64_t((w + p) / (p+1)) * uint64_t((h + r) / (r+1));
    };
    for(uint32_t qi = 0; qi < q; qi++)
    {
        uint32_t k = Q[qi].first, i = Q[qi].second;
        while(t+1 <= min(k, w-1) and F(t+1, k - (t+1)) <= F(t, k - t))
            t++;
        R[i] = F(t, k - t);
    }

    for(uint32_t i = 0; i < q; i++)
        cout << R[i] << "\n";
}
