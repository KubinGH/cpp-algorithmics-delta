#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using indexed_set = tree<
    T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update
>;

uint64_t
count_inv(const indexed_set<int32_t>& A, const indexed_set<int32_t>& B)
{
    uint64_t r = 0;
    if(A.size() <= B.size())
        for(int32_t a : A)
            r += B.order_of_key(a);
    else
    {
        r += (uint64_t) A.size() * B.size();
        for(int32_t b : B)
            r -= A.order_of_key(b);
    }
    return r;
}

void solve_tree(uint64_t& result, indexed_set<int32_t>& A)
{
    int32_t z;
    cin >> z;
    if(z == 0)
    {
        solve_tree(result, A);
        indexed_set<int32_t> B;
        solve_tree(result, B);

        auto r = count_inv(A, B);
        result += min(r, (uint64_t) A.size() * B.size() - r);

        if(A.size() <= B.size())
            A.swap(B);
        for(auto x : B)
            A.insert(x);
    }
    else
        A.insert(z);
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t _; cin >> _;
    uint64_t result = 0; indexed_set<int32_t> A;
    solve_tree(result, A);
    cout << result;
}
