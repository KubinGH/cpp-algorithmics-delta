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

    os_set<int> id;
    for(size_t i = 1; i <= n; i++)
        id.insert(i);

    size_t i = 0;
    while(not id.empty())
    {
        i += k;
        i %= id.size();
        auto it = id.find_by_order(i);
        cout << *it << ' ';
        id.erase(it);
    }
    cout << endl;
}
