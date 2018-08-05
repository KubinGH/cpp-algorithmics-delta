#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>
#include <functional>
#include <unordered_map>

using namespace std;
using namespace __gnu_pbds;

template<typename T> using ordered_set = tree<
    T, null_type, less<T>, rb_tree_tag,
    tree_order_statistics_node_update
>;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t k;
    cin >> k;
    ordered_set<pair<uint32_t, uint32_t>> S;
    unordered_map<uint32_t, uint32_t> M;
    uint32_t x;
    while(cin >> x)
    {
        if(x == -1u) break;
        else if(x == 0)
        {
            if(S.size() < k)
                cout << "NIE MA\n";
            else
            {
                auto it = S.find_by_order(k - 1);
                uint32_t y = it->first;
                cout << y << "\n";
                S.erase(it);
                if(--M[y] == 0)
                    M.erase(y);
            }
        }
        else
        {
            S.insert({x, M[x]++});
        }
    }
}
