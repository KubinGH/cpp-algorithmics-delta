#include <bits/stdc++.h>

using namespace std;

const int oo = INT_MAX/2-0xD;

int main()
{
    size_t n; int64_t x;
    cin >> n >> x;

    vector<int> A(n);
    for(auto& a : A)
        cin >> a;

    auto f = [&](pair<int, int64_t> st, int a) -> pair<int, int64_t> {
        if(st.second + a <= x)
            return {st.first, st.second + a};
        else
            return {st.first + 1, a};
    };

    vector<pair<int, int64_t>> R(1 << n, {+oo, +oo});
    R[0] = {0, +oo};
    for(size_t mask = 0; mask < (1u << n); mask++)
        for(size_t i = 0; i < n; i++)
            if(mask >> i & 1)
                R[mask] = min(R[mask], f(R[mask ^ (1 << i)], A[i]));

    cout << R.back().first << endl;
}
