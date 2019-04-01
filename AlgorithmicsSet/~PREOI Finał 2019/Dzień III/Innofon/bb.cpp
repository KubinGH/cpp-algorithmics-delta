#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct wavelet_tree
{
    struct wavelet_node
    {
        wavelet_node *left, *right;
        size_t n, a, b, c;
        vector<bool> B;
        vector<uint32_t> S;
        template<typename Iterator>
        wavelet_node(Iterator first, Iterator last, size_t _a, size_t _b) : a(_a), b(_b)
        {
            n = distance(first, last);
            c = a + (b - a) / 2;
            auto it = first;
            B.resize(n);
            for(size_t i = 0; i < n; i++, it++)
                B[i] = (*it > c);
            S.resize(n+1);
            for(size_t i = 0; i < n; i++)
                S[i+1] = S[i] + (B[i] == 0);
            if(a < b)
            {
                auto mid = stable_partition(first, last, [&](T x) { return x <= c; });
                left = first == mid ? nullptr : new wavelet_node(first, mid, a, c);
                right = mid == last ? nullptr : new wavelet_node(mid, last, c+1, b);
            }
        }
        size_t rank0(size_t i) const { return S[i]; }
        size_t rank1(size_t i) const { return i - S[i]; }
        size_t count_ge(size_t i, T value) const
        {
            if(b < value)
                return 0;
            else if(a >= value)
                return i;
            else
                return (!left  ? 0 :  left->count_ge(rank0(i), value))
                     + (!right ? 0 : right->count_ge(rank1(i), value));
        }
    } *root;

    template<typename Iterator>
    wavelet_tree(Iterator first, Iterator last, size_t A, size_t B)
    {
        vector<T> V(first, last);
        root = new wavelet_node(V.begin(), V.end(), A, B);
    }

    size_t count_ge(size_t i, size_t j, T value) const
    {
        return root->count_ge(j, value) - root->count_ge(i, value);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<pair<uint32_t, uint32_t>> P(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> P[i].first >> P[i].second;

    sort(P.begin(), P.end());

    vector<uint32_t> A(n), B(n);
    for(uint32_t i = 0; i < n; i++)
        tie(A[i], B[i]) = P[i];
    vector<uint32_t> V(2*n);
    copy(A.begin(), A.end(), V.begin());
    copy(B.begin(), B.end(), V.begin() + n);
    sort(V.begin(), V.end());

    wavelet_tree<uint32_t> W(B.begin(), B.end(), *min_element(B.begin(), B.end()), *max_element(B.begin(), B.end()) + 1);

    auto value = [&](uint32_t x, uint32_t X)
    {
        auto ex = lower_bound(A.begin(), A.end(), x); auto ix = ex - A.begin();
        auto eX = lower_bound(A.begin(), A.end(), X); auto iX = eX - A.begin();
        return (uint64_t) X * (n - iX) + (uint64_t) x * W.count_ge(ix, iX, x);
    };

    V.erase(unique(V.begin(), V.end()), V.end());

    uint64_t result = 0;
    for(uint32_t j = 1; j < V.size(); j++)
    {
        uint32_t b = 0;
        for(uint32_t i = 0; i < j; i++)
        {
            cerr << V[i] << ", " << V[j] << ": " << value(V[i], V[j]) << endl;
            result = max(result, value(V[i], V[j]));
            if(j > i+1 and j < V.size())
            {
            }
        }
        if(b > 1)
        {
            cout << "#";
            return 0;
        }
    }
    cout << result;
}
