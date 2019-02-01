#include <bits/stdc++.h>

using namespace std;

struct segment_tree
{
    vector<uint32_t> values;
    uint32_t w;
    segment_tree(uint32_t n)
    {
        w = 1 << __lg(2*n-1);
        values.resize(2*w);
    }
    void set(uint32_t p, uint32_t v)
    {
        p += w;
        values[p] = v;
        while(p > 1)
            p /= 2, values[p] = max(values[2*p], values[2*p+1]);
    }
    uint32_t get(uint32_t L, uint32_t R) const
    {
        uint32_t r = 0;
        for(L += w, R += w+1; L < R; L /= 2, R /= 2)
        {
            if(L % 2) r = max(r, values[L++]);
            if(R % 2) r = max(r, values[--R]);
        }
        return r;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<pair<uint64_t, uint32_t>> B(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> B[i].first, B[i].second = i;
    sort(B.begin(), B.end());
    vector<uint32_t> A(n);
    for(uint32_t i = 0, f = 0; i < n; i++)
    {
        if(i and B[i].first == B[i-1].first)
            f++;
        A[B[i].second] = i - f;
    }
    segment_tree X(n), Y(n);
    vector<uint32_t> P(n), R(n);
    for(uint32_t i = 0; i < n; i++)
        X.set(A[i], P[i] = 1 + (A[i] ? X.get(0, A[i]-1) : 0));
    for(uint32_t i = n; i --> 0; )
        Y.set(A[i], R[i] = 1 + (A[i] ? Y.get(0, A[i]-1) : 0));
    uint32_t r = 0;
    for(uint32_t i = 0; i < n; i++)
        r = max(r, P[i] + R[i] - 1);
    cout << n - r;
}
