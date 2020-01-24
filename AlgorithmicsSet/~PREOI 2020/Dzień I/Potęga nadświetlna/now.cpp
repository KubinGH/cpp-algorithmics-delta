#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

vector<uint> lims = {
    0, 0, 1'000'000'001, 1'000'001,
    31623, 3982, 1001, 373, 178, 101, 64, 44, 32, 25, 20,
    16, 14, 12, 11, 9, 8, 8, 7, 7, 6, 6, 5, 5, 5, 5, 4, 4,
    4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3
};

template<typename T, typename Fun>
T q_partition_point(T lo, T hi, Fun F)
{
    while(lo < hi)
    {
        auto mid = (lo + hi) / 2;
        if(F(mid))
            hi = mid;
        else
            lo = mid+1;
    }
    return lo;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    unordered_set<uint64_t> pre = {1};
    for(uint k = 4; k < lims.size(); k++)
        for(uint64_t i = 2; i < lims[k]; i++)
            pre.insert(power(i, k));

    auto decide = [&](uint64_t a) {
        if(pre.count(a))
            return true;
        for(auto k : {2, 3})
        {
            auto r = q_partition_point<uint64_t>(0, lims[k], [&](uint64_t x) {
                return power(x, k) >= a;
            });
            if(power(r, k) == a)
                return true;
        }
        return false;
    };

    size_t result = 0;
    for(size_t i = 0; i < n; i++)
    {
        uint64_t a;
        cin >> a;
        result += decide(a);
    }

    cout << result << '\n';
}
