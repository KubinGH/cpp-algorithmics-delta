#include <bits/stdc++.h>

using namespace std;

vector<int64_t> subset_sums(vector<int> A)
{
    const size_t n = A.size();
    vector<int64_t> R; R.reserve(1 << n);
    for(size_t mask = 0; mask < (1u << n); mask++)
    {
        R.emplace_back();
        for(size_t i = 0; i < n; i++)
            if(mask >> i & 1)
                R.back() += A[i];
    }
    return R;
}

int main()
{
    size_t n; int64_t x;
    cin >> n >> x;

    vector<int> A(n);
    for(auto& a : A)
        cin >> a;

    auto L = subset_sums(vector<int>(A.begin(), A.begin() + n/2)),
         R = subset_sums(vector<int>(A.begin() + n/2, A.end()));

    sort(L.begin(), L.end());
    sort(R.begin(), R.end());
    int64_t result = 0;
    for(auto s : L)
    {
        auto [it1, it2] = equal_range(R.begin(), R.end(), x - s);
        result += it2 - it1;
    }
    cout << result << endl;
}
