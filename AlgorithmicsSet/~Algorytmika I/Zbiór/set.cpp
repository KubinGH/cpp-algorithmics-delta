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
    
    size_t q;
    cin >> q;

    os_set<int> S;
    while(q --> 0)
    {
        size_t op, x;
        cin >> op >> x;
        if(op == 1)
            S.insert(x);
        else if(op == 2)
            S.erase(x);
        else if(op == 3)
            cout << *S.find_by_order(x - 1) << '\n';
    }
}
