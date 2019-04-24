#include <bits/stdc++.h>

using namespace std;

struct seg_t { uint32_t a, b; };

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    uint32_t n, k, l;
    cin >> n >> k >> l;

    vector<seg_t> x_seg(n), y_seg(n);
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x_seg[i] = {x1, x2};
        y_seg[i] = {y1, y2};
    }

    vector<uint32_t> vert(k), hori(l);
    for(uint32_t i = 0; i < k; i++)
        cin >> vert[i];
    for(uint32_t i = 0; i < l; i++)
        cin >> hori[i];

    auto solve_axis = [&](const vector<seg_t>& segments, const vector<uint32_t>& points) {
        const uint32_t s = segments.size();
        vector<uint32_t> A(s), B(s);
        for(uint32_t i = 0; i < s; i++)
            A[i] = segments[i].a, B[i] = segments[i].b;
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());
        uint64_t result = 0;
        for(auto v : points)
            result += (upper_bound(A.begin(), A.end(), v) - A.begin())
                    - (lower_bound(B.begin(), B.end(), v) - B.begin());
        return result;
    };
    cout << solve_axis(x_seg, vert) + solve_axis(y_seg, hori);
}
