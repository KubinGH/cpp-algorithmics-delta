#include <bits/stdc++.h>

using namespace std;


vector<pair<pair<int, int>, int>> harmonic(int n, int init = 1)
{
    vector<pair<pair<int, int>, int>> re;
    re.reserve(2 * floor(sqrt(n)));
    for(int i = init, j; i <= n; i = j + 1)
    {
        j = n / (n / i);
        re.emplace_back(make_pair(i, j), n / i);
    }
    re.emplace_back(make_pair(n + 1, INT_MAX), 0);
    return re;
}

vector<pair<int, int>> candidates(int a, int b)
{
    vector<int> candy;
    for(int x = 1; x*x <= a; x++)
        if(a % x == 0)
            candy.push_back(x);
    for(size_t i = candy.size() - (candy.back() * candy.back() == a); i --> 0; )
        candy.push_back(a / candy[i]);


    auto A = harmonic(a, b-a+2), B = harmonic(b, b-a+2);

    vector<int> points;
    points.reserve(2 * (A.size() + B.size()));
    size_t mid = 0;
    for(auto& ct : {A, B})
    {
        for(auto [ij, k] : ct)
            points.push_back(ij.first), points.push_back(ij.second);
        if(not mid) mid = points.size();
    }
    inplace_merge(points.begin(), points.begin() + mid, points.end());

    vector<pair<int, int>> intervals = {{1, b-a+1}};
    intervals.reserve(points.size());
    size_t i = 0, j = 0;
    bool inside = false;
    for(auto p : points) if(p < INT_MAX)
    {
        while(A[i].first.second < p) i++;
        while(B[j].first.second < p) j++;

        if(A[i].second != B[j].second)
        {
            if(not inside)
                intervals.emplace_back(p, p), inside = true;
            else
                intervals.back().second = p;
        }
        else
            inside = false;
    }


    vector<pair<int, int>> fix;
    fix.reserve(candy.size() + intervals.size());

    i = 0;
    for(auto k : candy)
    {
        while(i < intervals.size() and intervals[i].second < k)
            fix.push_back(intervals[i++]);

        if(not (i < intervals.size() and intervals[i].first <= k and k <= intervals[i].second))
            fix.emplace_back(k, k);
    }
    while(i < intervals.size())
        fix.push_back(intervals[i++]);
    swap(fix, intervals);


    return intervals;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    while(n --> 0)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        auto X = candidates(a, b), Y = candidates(c, d);

        int result = 0;

        size_t i = X.size(), j = Y.size();
        while(i and j)
        {
            auto [x1, x2] = X[i-1];
            auto [y1, y2] = Y[j-1];
            if(max(x1, y1) <= min(x2, y2))
            {
                result = max(result, min(x2, y2));
                break;
            }
            (X[i-1] > Y[j-1] ? i : j)--;
        }

        cout << result << '\n';
    }
}
