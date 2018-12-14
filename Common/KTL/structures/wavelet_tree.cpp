// Wavelet tree with a few operations implemented.
// Based on "Wavelet trees for all" and
// "Wavelet trees in competitive programming"
// TODO: add median and value scaling optimizations.
//       (requires external constructor)

// Last revision: October 2018

#include <cstddef>
#include <vector>
#include <algorithm>

using std::size_t; using std::vector;
using std::stable_partition;
using std::min_element; using std::max_element;

template<typename Arg, typename MonoOperation>
Arg first_true(Arg lo, Arg hi, MonoOperation f)
{
    while(lo < hi)
    {
        Arg mid = (lo + hi) / 2;
        if(f(mid))
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}

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
        // Initialize the tree over the range [first, last)
        // using the alphabet [a..b]
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
        // Return the count of zeroes in the bitmap B over [0, i)
        size_t rank0(size_t i) const { return Bc[i]; }
        size_t rank1(size_t i) const { return i - rank0(i); }
        // Return the index of the x-th 0
        size_t select0(size_t x) const
            { return first_true(0, n, [x](size_t i) { return rank0(i+1) >= x; }); }
        size_t select1(size_t x) const
            { return first_true(0, n, [x](size_t i) { return rank1(i+1) >= x; }); }
        // Return the count of elements that are >= k in the range [0, i)
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
        // Return the element at index i
        T index(size_t i) const
        {
            if(a == b)
                return a;
            else if(B[i] == 0)
                return left->index(rank0(i));
            else
                return right->index(rank1(i));
        }
        // Return the element at index i, in the substring [L..R)
        // assuming it was sorted
        T quantile(size_t i, size_t L, size_t R) const
        {
            if(a == b)
                return a;
            else if(i < rank0(R) - rank0(L))
                return left->quantile(i, rank0(L), rank0(R));
            else
                return right->quantile(i - (rank0(R) - rank0(L)), rank1(L), rank1(R));
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
    size_t count_equal(size_t i, size_t j, T k)
        { return count_greater_or_equal(i, j, k) - count_greater(i, j, k); }
    size_t count_lesser(size_t i, size_t j, T k)
        { return (j - i) - count_greater_or_equal(i, j, k); }
    size_t count_lesser_or_equal(size_t i, size_t j, T k)
        { return (j - i) - count_greater(i, j, k); }
    T index(size_t i) const { return root->index(i); }
    T quantile(size_t i, size_t L, size_t R) const { return root->quantile(i, L, R); }
    T quantile(size_t i) { return quantile(i, 0, root->n); }
};
