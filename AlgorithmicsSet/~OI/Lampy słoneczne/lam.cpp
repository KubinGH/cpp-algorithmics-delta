#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using os_set = tree<
    T, null_type, less<T>, rb_tree_tag,
    tree_order_statistics_node_update
>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    int64_t a, b, c, d;
    cin >> a >> b >> c >> d;

    auto det = a*d - b*c;

    if(det < 0)
        swap(a, c), swap(b, d);

    vector<pair<int64_t, int64_t>> A(n);
    map<int64_t, vector<size_t>> lines;
    for(size_t i = 0; i < n; i++)
    {
        auto& [x, y] = A[i];
        int64_t x1, y1;
        cin >> x1 >> y1;
        if(det)
            x = d*x1 - c*y1, y = -b*x1 + a*y1, lines[0].push_back(i);
        else
            x = -b*x1 + a*y1, y = a*x1 + b*y1, lines[x].push_back(i);
    }

    map<int, size_t> sx, sy;
    for(auto& [x, y] : A) sx[x], sy[y];
    size_t fx = 0, fy = 0;
    for(auto& [k, v] : sx) v = fx++;
    for(auto& [k, v] : sy) v = fy++;
    for(auto& [x, y] : A) x = sx[x], y = sy[y];

    vector<int> R(n);
    for(auto& r : R)
        cin >> r;

    vector<int> T(n);
    for(const auto& [_, indices] : lines)
    {
        for(auto s : indices)
        {
            if(not R[s])
                continue;
            R[s] = 0;
            vector<size_t> tovis = {s};
            while(not tovis.empty())
            {
                auto i = tovis.back(); tovis.pop_back();
                T[i] = s + 1;
                for(auto j : indices)
                    if(R[j] and A[j].first >= A[i].first and A[j].second >= A[i].second and not --R[j])
                        tovis.push_back(j);
            }
        }
    }

    for(auto t : T)
        cout << t << ' ';
    cout << endl;
}
