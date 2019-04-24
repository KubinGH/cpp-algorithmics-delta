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
        const uint32_t s = segments.size(), p = points.size();

        vector<uint32_t> A;
        A.reserve(2*s + p);
        for(uint32_t i = 0; i < s; i++)
            A.push_back(segments[i].a), A.push_back(segments[i].b);
        for(uint32_t i = 0; i < p; i++)
            A.push_back(points[i]);

        sort(A.begin(), A.end());
        A.erase(unique(A.begin(), A.end()), A.end());
        unordered_map<uint32_t, uint32_t> T;
        T.reserve(2 * A.size());
        for(uint32_t i = 0; i < A.size(); i++)
            T[A[i]] = i;

        const uint32_t max_coor = A.size();
        vector<uint32_t> diff_array(max_coor + 1);
        for(auto q : segments)
        {
            diff_array[T[q.a]]++;
            diff_array[T[q.b] + 1]--;
        }
        vector<uint32_t> crossed(max_coor + 1);
        partial_sum(diff_array.begin(), diff_array.end(), crossed.begin());

        uint64_t result = 0;
        for(auto v : points)
            result += crossed[T[v]];
        return result;
    };
    cout << solve_axis(x_seg, vert) + solve_axis(y_seg, hori);
}
