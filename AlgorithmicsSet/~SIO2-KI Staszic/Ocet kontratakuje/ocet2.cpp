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
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    indexed_set<pair<int, size_t>> A;
    size_t k = 0;
    while(n--)
    {
        size_t t;
        cin >> t;
        if(t == 1)
        {
            size_t v;
            cin >> v;
            A.insert({v, n});
        }
        else if(t == 0)
            cout << (*A.find_by_order(k++)).first << "\n";
    }
}
