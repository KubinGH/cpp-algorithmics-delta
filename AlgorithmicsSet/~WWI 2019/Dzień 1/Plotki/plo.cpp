#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

using namespace __gnu_pbds;

template<typename T>
using order_statistics_set = tree<
    T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update
>;


vector<size_t> pinverse(const vector<size_t>& P)
{
    vector<size_t> Q(P.size());
    for(size_t i = 0; i < P.size(); i++)
        Q[P[i]] = i;
    return Q;
}

struct fenwick_tree_2d
{
    size_t n;
    vector<order_statistics_set<size_t>> F;

    fenwick_tree_2d(size_t _n) : n(_n), F(n+1) {}

    static constexpr size_t lsb(size_t x) { return x & -x; }

    void push(size_t x, size_t y)
    {
        y++;
        while(y <= n)
            F[y].insert(x), y += lsb(y);
    }

    int get_prefix(size_t x, size_t y)
    {
        int r = 0;
        while(y)
            r += F[y].order_of_key(x), y -= lsb(y);
        return r;
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<size_t> A(n), B(n), C(n);

    for(size_t i = 0; i < n; i++)
        cin >> A[i];
    for(size_t i = 0; i < n; i++)
        cin >> B[i];
    for(size_t i = 0; i < n; i++)
        cin >> C[i];

    auto B1 = pinverse(B), C1 = pinverse(C);

    uint64_t result = 0;

    fenwick_tree_2d T(n);

    for(size_t k = 0; k < n; k++)
    {
        size_t x = A[k], i = B1[x], j = C1[x];
        result += T.get_prefix(i+1, j+1);

        T.push(i+1, j+1);
    }

    cout << result;
}
