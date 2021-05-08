#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

template<typename T, typename Cmp = less<T>>
using os_set = __gnu_pbds::tree<
    T, __gnu_pbds::null_type, Cmp, __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update
>;

vector<size_t> count_dom(const vector<pair<int, int>>& A)
{
    const size_t n = A.size();

    vector<size_t> I(n);
    iota(I.begin(), I.end(), 0);
    sort(I.begin(), I.end(), [&](size_t i, size_t j) {
        return A[i] < A[j];
    });
    vector<size_t> out(n);
    os_set<pair<int, size_t>> Y;

    for(auto i : I)
    {
        auto y = A[i].second;
        out[i] = Y.order_of_key({y + 1, 0});
        Y.insert({y, i});
    }
    return out;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<pair<int, int>> A(n);
    for(auto& [x, y] : A)
        cin >> x >> y;

    for(auto& [x, y] : A)
        x = -x;
    for(auto c : count_dom(A))
        cout << c << ' ';
    cout << endl;
    for(auto& [x, y] : A)
        x = -x, y = -y;
    for(auto c : count_dom(A))
        cout << c << ' ';
    cout << endl;
}
