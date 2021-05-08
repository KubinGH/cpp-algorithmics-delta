#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, k;
    cin >> n >> k;

    vector<pair<int, int>> A(n);
    for(auto& [l, r] : A)
        cin >> l >> r;
    sort(A.begin(), A.end());
    vector<tuple<int, int, size_t>> B(n);
    for(size_t i = 0; i < n; i++)
        B[i] = {A[i].second, -A[i].first, i};
    sort(B.begin(), B.end());

    multiset<size_t> freed;
    for(size_t i = 0; i < k; i++)
        freed.insert(0);

    size_t result = 0;
    for(size_t i = 0; i < n; i++)
    {
        auto [r, _, j] = B[i];
        auto it = freed.upper_bound(j);
        if(it != freed.begin())
        {
            result++;
            auto l = lower_bound(A.begin(), A.end(), pair(r, r)) - A.begin();
            freed.erase(--it);
            freed.insert(l);
        }
    }

    cout << result << endl;
}
