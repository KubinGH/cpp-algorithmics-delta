#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct wavelet_tree
{
    T a, b;
    struct node
    {
        size_t n;
        T a, b, c;
        vector<bool> B;
        vector<size_t> Bs;
        unique_ptr<node> left, right;
        template<typename Iterator>
        node(Iterator first, Iterator last, T _a, T _b)
            : n(distance(first, last)), a(_a), b(_b), c(a + (b-a+1)/2), B(n)
        {
            for(size_t i = 0; i < n; i++)
                B[i] = (first[i] >= c);
            Bs.resize(n+1);
            for(size_t i = 0; i < n; i++)
                Bs[i+1] = Bs[i] + (B[i] == 0);
            if(a < b)
            {
                auto mid = stable_partition(first, last, [&](T x) { return x < c; });
                left = unique_ptr<node>(first == mid ? nullptr : new node(first, mid, a, c-1));
                right = unique_ptr<node>(mid == last ? nullptr : new node(mid, last, c, b));
            }
        }

        size_t rank0(size_t i) const { return Bs[i]; }
        size_t rank1(size_t i) const { return i - Bs[i]; }

        T quantile(size_t i, size_t L, size_t R) const
        {
            if(a == b)
                return a;
            else if(i < rank0(R) - rank0(L))
                return left->quantile(i, rank0(L), rank0(R));
            else
                return right->quantile(i - (rank0(R) - rank0(L)), rank1(L), rank1(R));
        }
    };
    unique_ptr<node> root;

    template<typename Iterator>
    wavelet_tree(Iterator first, Iterator last)
        : a(*min_element(first, last)), b(*max_element(first, last))
    {
        vector<T> seq(first, last);
        root = unique_ptr<node>(new node(seq.begin(), seq.end(), a, b));
    }

    T quantile(size_t i, size_t L, size_t R) const
    {
        return root->quantile(i, L, R);
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, k, l1, l2;
    cin >> n >> k >> l1 >> l2;

    vector<int> A(n), S(n+1);
    for(size_t i = 0; i < n; i++)
        cin >> A[i];
    partial_sum(A.begin(), A.end(), S.begin() + 1);

    wavelet_tree<int> W(S.begin(), S.end());

    vector<size_t> next(n+1);
    priority_queue<pair<int, size_t>> Q;

    auto push_next = [&](size_t i) {
        size_t l = max(i, l2) - l2, r = max(i, l1-1) - l1 + 1;
        if(next[i] < (r - l))
            Q.emplace(S[i] - W.quantile(next[i], l, r), i), next[i]++;
    };

    for(size_t i = l1; i <= n; i++)
        push_next(i);

    size_t c = 0;
    int64_t result = 0;
    while(not Q.empty() and c < k)
    {
        auto p = Q.top(); Q.pop();
        size_t i; int v;
        tie(v, i) = p;
        result += v; c++;
        push_next(i);
    }

    if(c == k)
        cout << result;
    else
        cout << "COLLOREDO";
    cout << endl;
}
