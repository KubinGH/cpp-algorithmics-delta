#include <bits/stdc++.h>

using namespace std;

struct fenwick_tree
{
    size_t n;
    vector<int> F;
    fenwick_tree(size_t _n) : n(_n), F(n+1) {}
    static constexpr size_t lsb(size_t x) { return x & -x; }
    void delta(size_t p, int v)
    {
        p++;
        while(p <= n)
            F[p] += v, p += lsb(p);
    }
    int get_prefix(size_t p)
    {
        int r = 0;
        while(p)
            r += F[p], p -= lsb(p);
        return r;
    }
    int get(size_t a, size_t b)
    {
        return get_prefix(b) - get_prefix(a);
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    vector<bool> A(n);
    fenwick_tree F(n);
    string S;
    cin >> S;
    for(size_t i = 0; i < n; i++)
    {
        A[i] = (S[i] == 'P');
        F.delta(i, A[i]);
    }

    auto inversions = [&](size_t i) -> int {
        if(A[i])
            return n - (i+1) - F.get(i+1, n);
        else
            return F.get_prefix(i);
    };

    int64_t result = 0;
    for(size_t i = 0; i < n; i++)
        result += inversions(i);
    result /= 2;

    cout << result << '\n';
    while(q --> 0)
    {
        size_t i;
        cin >> i; i--;
        result -= inversions(i);
        A[i] = not A[i];
        F.delta(i, A[i] ? 1 : -1);
        result += inversions(i);
        cout << result << '\n';
    }
}
