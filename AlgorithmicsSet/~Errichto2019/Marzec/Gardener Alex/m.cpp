#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;

struct segment_tree
{
    size_t w;
    vector<int> values, mutate;

    segment_tree(size_t n) : w(1 << __lg(2*n-1)), values(2*w), mutate(2*w) {}

    void pull(size_t i, size_t nodeL, size_t nodeR)
    {
        if(nodeL < nodeR)
            mutate[2*i] += mutate[i], mutate[2*i+1] += mutate[i];
        values[i] += mutate[i];
        mutate[i] = 0;
    }

    int get(size_t i, size_t nodeL, size_t nodeR, size_t getL, size_t getR)
    {
        pull(i, nodeL, nodeR);
        if(nodeR < getL or getR < nodeL)
            return 0;
        else if(getL <= nodeL and nodeR <= getR)
            return values[i];
        else
        {
            auto mid = (nodeL+nodeR)/2;
            return max(get(2*i, nodeL, mid, getL, getR),
                       get(2*i+1, mid+1, nodeR, getL, getR));
        }
    }
    void mut(size_t i, size_t nodeL, size_t nodeR, size_t getL, size_t getR, int x)
    {
        pull(i, nodeL, nodeR);
        if(nodeR < getL or getR < nodeL)
            {}
        else if(getL <= nodeL and nodeR <= getR)
            mutate[i] += x, pull(i, nodeL, nodeR);
        else
        {
            auto mid = (nodeL+nodeR)/2;
            mut(2*i, nodeL, mid, getL, getR, x);
            mut(2*i+1, mid+1, nodeR, getL, getR, x);
            values[i] = max(values[2*i], values[2*i+1]);
        }
    }

    int get(size_t L, size_t R) { return L<R ? get(1, 0, w-1, L, R-1) : 0; }
    void mut(size_t L, size_t R, int x) { if(L<R) mut(1, 0, w-1, L, R-1, x); }
};

template<typename T, typename Fun>
T first_true(T lo, T hi, Fun f)
{
    while(lo < hi)
    {
        auto mid = (lo+hi)/2;
        if(f(mid))
            hi = mid;
        else
            lo = mid+1;
    }
    return lo;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<uint> A(2*n);
    for(size_t i = 0; i < n; i++)
        cin >> A[i], A[i+n] = --A[i];

    const size_t m = 2*n;
    vector<vector<pair<uint, size_t>>> T(__lg(m)+1, vector<pair<uint, size_t>>(m));
    for(size_t i = 0; i < m; i++)
        T[0][i] = {A[i], i};
    for(size_t k = 0, p = 1; 2*p <= m; k++, p *= 2)
        for(size_t i = 0; i+2*p <= m; i++)
            T[k+1][i] = min(T[k][i], T[k][i+p]);

    auto rmq = [&](size_t i, size_t j) {
        if(i == j) return make_pair(UINT_MAX, SIZE_MAX);
        const auto k = __lg(j - i);
        return min(T[k][i], T[k][j-(1<<k)]);
    };

    vector<int> anc(n);
    function<void(size_t, size_t, int)> get_depth = [&](size_t i, size_t j, int a) {
        if(i == j) return;
        auto k = rmq(i, j).second;
        anc[k] = a;
        get_depth(i, k, a+1);
        get_depth(k+1, j, a+1);
    };
    get_depth(0, n, 0);

    segment_tree tree(m);
    for(size_t i = 0; i < n; i++)
        tree.mut(i, i+1, anc[i]);

    auto leftmost_less = [&](size_t i, size_t j, uint x) {
        return i + first_true((size_t)0, j-i, [&](size_t mid) { return rmq(i, i+mid+1).first < x; });
    };
    auto rightmost_less = [&](size_t i, size_t j, uint x) {
        return j-1 - first_true((size_t)0, j-i, [&](size_t mid) { return rmq(j-mid-1, j).first < x; });
    };


    pair<int, size_t> result = {INT_MAX, 0};
    for(size_t j = 0; j < n; j++)
    {
        result = min(result, {tree.get(j, j+n), j});
        auto x = A[j];
        if(x)
        {
            auto l = leftmost_less(j, j+n, x), r = rightmost_less(j, j+n, x);
            tree.mut(j+1, l, -1);
            tree.mut(r+1, n+j, +1);
            tree.mut(n+j, n+j+1, tree.get(r, r+1) + 1);
        }
    }

    cout << result.first+1 << ' ' << result.second << endl;
}
