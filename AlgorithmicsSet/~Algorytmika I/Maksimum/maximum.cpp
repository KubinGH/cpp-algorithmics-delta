#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    const size_t block = floor(sqrt(n));
    vector<uint> A(n);
    vector<vector<uint>> I;
    for(size_t i = 0; i < n; i++)
    {
        if(i % block == 0)
            I.emplace_back();
        cin >> A[i];
        I.back().push_back(i);
    }

    auto cmp = [&](size_t i, size_t j) {
        return A[i] < A[j];
    };

    for(auto& b : I)
        sort(b.begin(), b.end(), cmp);

    auto get_max = [&]() {
        uint r = 0;
        for(auto& d : I)
            r = max(r, A[d.back()]);
        return r;
    };

    cout << get_max() << '\n';
    while(m --> 0)
    {
        size_t i, x;
        cin >> i >> x; i--;

        auto& b = I[i / block];
        b.erase(find(b.begin(), b.end(), i));
        A[i] = x;
        b.insert(upper_bound(b.begin(), b.end(), i, cmp), i);

        cout << get_max() << '\n';
    }
}
