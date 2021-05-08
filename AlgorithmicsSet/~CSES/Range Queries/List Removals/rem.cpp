#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
template<typename T>
using os_set = tree<
    T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update
>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    os_set<pair<size_t, int>> keys;
    for(size_t i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        keys.insert({i, a});
    }

    for(size_t i = 0; i < n; i++)
    {
        size_t p;
        cin >> p; p--;
        auto it = keys.find_by_order(p);
        cout << it->second << ' ';
        keys.erase(it);
    }
    cout << endl;
}
