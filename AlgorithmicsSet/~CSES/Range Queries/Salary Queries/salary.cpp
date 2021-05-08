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

    size_t n, q;
    cin >> n >> q;

    vector<int> A(n);
    for(auto& a : A)
        cin >> a;

    os_set<pair<int, size_t>> keys;
    for(size_t i = 0; i < n; i++)
        keys.insert({A[i], i});

    while(q --> 0)
    {
        char t;
        cin >> t;
        if(t == '?')
        {
            int a, b;
            cin >> a >> b;
            cout << keys.order_of_key({b+1, 0}) - keys.order_of_key({a, 0}) << '\n';
        }
        else if(t == '!')
        {
            size_t p; int v;
            cin >> p >> v; p--;
            keys.erase({A[p], p});
            keys.insert({A[p] = v, p});
        }
    }
}
