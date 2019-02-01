#include <bits/stdc++.h>

using namespace std;

template<typename T, typename ChildrenOp>
struct segment_tree
{
    vector<T> values;
    size_t w;
    ChildrenOp F;
    segment_tree(size_t n, ChildrenOp f = {})
    {
        F = move(f);
        w = 1 << __lg(2*n-1);
        values.resize(2*w, identity_element(F));
    }
    void set(size_t i, T value)
    {
        i += w;
        values[i] = value; i /= 2;
        while(i) values[i] = F(values[2*i], values[2*i+1]), i /= 2;
    }
    T get(size_t getL, size_t getR)
    {
        T result = identity_element(F);
        for(getL += w, getR += w+1; getL < getR; getL /= 2, getR /= 2)
        {
            if(getL % 2) result = F(result, values[getL++]);
            if(getR % 2) result = F(result, values[--getR]);
        }
        return result;
    }
};

struct max_u32 { uint32_t operator() (uint32_t a, uint32_t b) { return a>b ? a : b; } };
uint32_t identity_element(max_u32) { return 0; }

template<typename T>
struct wavelet_tree
{
    struct wavelet_node
    {
        size_t n;
        T a, b;
        vector<bool> B;
        vector<size_t> Bc;
        wavelet_node *left, *right;
        template<typename Iterator>
        wavelet_node(Iterator first, Iterator last, T _a, T _b)
            : n(distance(first, last)), a(_a), b(_b), B(n)
        {
            const T c = a + (b-a)/2;
            for(size_t i = 0; i < n; i++)
                B[i] = (first[i] > c);
            Bc.resize(n+1);
            for(size_t i = 0; i < n; i++)
                Bc[i+1] = Bc[i] + (B[i] == 0);
            if(a < b)
            {
                auto mid = stable_partition(first, last, [c](T x) { return x <= c; });
                left = first == mid ? nullptr : new wavelet_node(first, mid, a, c);
                right = mid == last ? nullptr : new wavelet_node(mid, last, c+1, b);
            }
        }
        size_t rank0(size_t i) const { return Bc[i]; }
        size_t rank1(size_t i) const { return i - rank0(i); }
        size_t count_greater_or_equal(size_t i, T k) const
        {
            if(b < k)
                return 0;
            else if(a >= k)
                return i;
            else
                return (!left  ? 0 :  left->count_greater_or_equal(rank0(i), k))
                     + (!right ? 0 : right->count_greater_or_equal(rank1(i), k));
        }
    } *root;
    T a, b;
    template<typename Iterator>
    wavelet_tree(Iterator first, Iterator last, T _a, T _b) : a(_a), b(_b)
    {
        vector<T> S(first, last);
        root = new wavelet_node(S.begin(), S.end(), a, b);
    }
    template<typename Iterator>
    wavelet_tree(Iterator first, Iterator last)
        : wavelet_tree(first, last, *min_element(first, last), *max_element(first, last)) {}
    size_t count_greater_or_equal(size_t i, size_t j, T k)
        { return root->count_greater_or_equal(j, k) - root->count_greater_or_equal(i, k); }
    size_t count_greater(size_t i, size_t j, T k)
        { return count_greater_or_equal(i, j, k+1); }
    size_t count_lesser_or_equal(size_t i, size_t j, T k)
        { return (j - i) - count_greater(i, j, k); }
};

using pair_u32 = pair<uint32_t, uint32_t>;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    vector<pair_u32> B(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> B[i].first, B[i].second = i;
    sort(B.begin(), B.end());
    vector<uint32_t> A(n);
    for(uint32_t i = 0; i < n; i++)
        A[B[i].second] = i;
    segment_tree<uint32_t, max_u32> X_T(n);
    vector<uint32_t> X(n);
    for(uint32_t i = 0; i < n; i++)
    {
        X[i] = X_T.get(A[i]+1, n-1);
        X_T.set(A[i], i+1);
    }
    wavelet_tree<uint32_t> W(X.begin(), X.end(), 0, n-1);
    while(q --> 0)
    {
        uint32_t a, b;
        cin >> a >> b; a--;
        cout << W.count_lesser_or_equal(a, b, a) << "\n";
    }
}
