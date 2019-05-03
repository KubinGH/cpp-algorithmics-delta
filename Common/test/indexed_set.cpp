#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using indexed_set = tree<
    T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update
>;

int main()
{
    indexed_set<int> S;
    S.insert(1); S.insert(4); S.insert(7);
    cout << *S.find_by_order(1) << endl; // 4
    cout << S.order_of_key(0) << " " << S.order_of_key(4) << endl; // 0 1
}
