#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

template<typename T, typename Cmp = less<T>>
using os_set = __gnu_pbds::tree<
    T, __gnu_pbds::null_type, Cmp, __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update
>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, k;
    cin >> n >> k;

    vector<int> A(n);
    for(auto& a : A)
        cin >> a;

    os_set<pair<int, size_t>> val;
    for(size_t i = 0; i < k; i++)
        val.insert({A[i], i});

    cout << val.find_by_order((k-1)/2)->first << ' ';

    for(size_t i = k; i < n; i++)
    {
        val.erase({A[i-k], i-k});
        val.insert({A[i], i});
        cout << val.find_by_order((k-1)/2)->first << ' ';
    }
    cout << endl;
}
