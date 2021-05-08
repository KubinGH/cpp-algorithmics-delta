#include <bits/stdc++.h>

using namespace std;

const int oo = INT_MAX/3 - 0xD;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<int> A(n);
    for(auto& a : A)
        cin >> a;

    map<pair<int, int>, int> dist, prev_dist;
    queue<tuple<size_t, int, int>> tovis;
    auto maybe = [&](size_t i, int x1, int x0, int d) {
        if(not dist.count({x1, x0}) or d < dist[{x1, x0}])
            dist[{x1, x0}] = d, tovis.emplace(i, x1, x0);
    };
    const int mx = (2 * accumulate(A.begin(), A.end(), 0)) / n + 0xD;

    for(int x = A[0]-mx; x <= A[0]; x++)
        maybe(0, 0, x, abs(x));

    vector<int> pref(n + 1), suff(n + 1);
    for(size_t i = n; i --> 0; )
        suff[i] = suff[i+1] + A[i];
    for(size_t i = 0; i < n; i++)
        pref[i+1] = pref[i] + A[i];

    int result = +oo;
    size_t li = SIZE_MAX;
    while(not tovis.empty())
    {
        auto [i, x1, x0] = tovis.front(); tovis.pop();

        if(i != li)
            li = i, swap(prev_dist, dist), dist.clear();
        if(not prev_dist.count({x1, x0}))
            continue;

        const auto d = prev_dist[{x1, x0}];
        prev_dist.erase({x1, x0});

        if(A[i] + x1 - x0 > mx)
            continue;
        if(x0 > pref[i + 1] or -x0 > suff[i])
            continue;

        if(i+1 < n)
        {
            int xx = A[i+1] - A[i] + 2*x0 - x1;
            for(int x = xx-1; x <= xx+1 and x <= A[i+1] + x0; x++)
                maybe(i + 1, x0, x, abs(x) + d);
        }
        else if(x0 == 0)
            result = min(result, d);
    }

    cout << result << endl;
}
