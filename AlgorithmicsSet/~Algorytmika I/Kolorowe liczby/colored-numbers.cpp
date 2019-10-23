#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, k;
    cin >> n >> k;

    vector<int64_t> A(n);
    for(auto& a : A)
        cin >> a;

    auto inc = [&](pair<int64_t, size_t> p, int64_t v) {
        return pair<int64_t, size_t>(p.first + v, p.second + 1);
    };
    auto run = [&](int64_t malus) {
        pair<int64_t, size_t> curr{}, last{}, last2nd{};
        for(size_t i = 0; i < n; i++)
        {
            last2nd = last; last = curr;
            curr = max(last, inc(last2nd, A[i] - malus));
        }
        return curr;
    };

    auto base_resulto = run(0);
    if(base_resulto.second <= k)
    {
        cout << base_resulto.first;
        return 0;
    }

    int64_t lo = 0, hi = *max_element(A.begin(), A.end()) + 0xD;
    while(lo < hi)
    {
        auto mid = lo + (hi-lo)/2;

        auto state = run(mid);

        if(state.second <= k)
            hi = mid;
        else
            lo = mid+1;
    }

    auto p = run(lo), q = run(lo-1);
    p.first += p.second*lo;
    q.first += q.second*(lo-1);

    if(p.second == k)
        cout << p.first;
    else
    {
        auto slope = (q.first - p.first) / (q.second - p.second);
        auto resulto = p.first + slope*(k - p.second);
        cout << resulto;
    }
}
