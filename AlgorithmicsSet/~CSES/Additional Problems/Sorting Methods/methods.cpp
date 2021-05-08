#include <bits/stdc++.h>

using namespace std;

struct fenwick_tree
{
    size_t n;
    vector<int> F;
    fenwick_tree(size_t _n) : n(_n), F(n+1) {}

    void delta(size_t p, int v)
    {
        p++;
        while(p <= n)
            F[p] = max(F[p], v), p += p & -p;
    }

    int get_prefix(size_t p) const
    {
        int r = 0;
        while(p)
            r = max(r, F[p]), p &= p - 1;
        return r;
    }
};

vector<size_t> inverse(vector<size_t> A)
{
    vector<size_t> B(A.size());
    for(size_t i = 0; i < A.size(); i++)
        B[A[i]] = i;
    return B;
}

int64_t rytter(vector<size_t> A, int k = -1)
{
    if(k == -1)
        for(auto a : A)
            k = max(k, a ? int(__lg(a)) : 0);
    vector<size_t> B[2];
    int64_t r = 0;
    for(auto a : A)
    {
        B[a >> k & 1].push_back(a);
        if(not (a >> k & 1))
            r += B[1].size();
    }
    return r + (k ? rytter(B[0], k - 1) + rytter(B[1], k - 1) : 0);
}

int ncycles(vector<size_t> A)
{
    const size_t n = A.size();
    vector<bool> vis(n);
    int result = 0;
    for(size_t s = 0; s < n; s++)
      if(not vis[s])
    {
        size_t v = s;
        while(not vis[v])
            vis[v] = true, v = A[v];
        result++;
    }
    return result;
}

vector<int> increasing_till(vector<size_t> A)
{
    const size_t n = A.size();
    fenwick_tree F(n);
    vector<int> R(n);
    for(size_t i = 0; i < n; i++)
        F.delta(A[i], R[i] = 1 + F.get_prefix(A[i]));
    return R;
}

vector<int> consecutive_till(vector<size_t> A)
{
    const size_t n = A.size();
    vector<int> R(n);
    auto B = inverse(A);
    for(size_t i = 0; i < n; i++)
        R[i] = 1 + (A[i] ? R[B[A[i]-1]] : 0);
    return R;
}

int max(vector<int> A)
{
    return *max_element(A.begin(), A.end());
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<size_t> A(n);
    for(auto& a : A)
        cin >> a, a--;

    auto I = increasing_till(A), C = consecutive_till(A);
    auto nth = find(A.begin(), A.end(), n - 1) - A.begin();

    cout << rytter(A) << " " << n-ncycles(A) << " ";
    cout << n-max(I) << " " << n-C[nth] << endl;
}
