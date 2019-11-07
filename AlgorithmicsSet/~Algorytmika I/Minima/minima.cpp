#include <bits/stdc++.h>
#include <ktl/structures/segment_tree.cpp>

using namespace std;

const int64_t oo = INT64_MAX / 3;

struct minfun { int64_t operator() (int64_t a, int64_t b) { return min(a, b); } };

struct mutadd
{
    void operator() (size_t i, size_t nodeL, size_t nodeR, vector<int64_t>& values, vector<int64_t>& mutate)
    {
        values[i] += mutate[i];
        if(nodeL < nodeR)
        {
            mutate[2*i] += mutate[i];
            mutate[2*i+1] += mutate[i];
        }
        mutate[i] = 0;
    }
};
int64_t identity_element(minfun) { return oo; }
int64_t identity_element(mutadd) { return 0; }

using tree = segment_tree_i<
    int64_t, minfun,
    int64_t, mutadd, plus<int64_t>
>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    vector<int64_t> A(n);
    for(int64_t& a : A)
        cin >> a;

    tree T(n);
    for(size_t i = 0; i < n; i++)
        T.mut(i, i, A[i] - oo);

    while(q --> 0)
    {
        char c;
        cin >> c;

        if(c == '+')
        {
            size_t l, r; int64_t v;
            cin >> l >> r >> v; l--; r--;
            T.mut(l, r, v);
        }
        else if(c == '?')
        {
            size_t l, r;
            cin >> l >> r; l--; r--;
            cout << T.get(l, r) << '\n';
        }
    }
}
