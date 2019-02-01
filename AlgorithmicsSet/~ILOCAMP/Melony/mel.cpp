#include <bits/stdc++.h>
#define REG(__value) \
{                                                                       \
    result = max(result, (__value));                                    \
    if(0) cerr << "register " << (__value) << " from line " << __LINE__ << endl;   \
}

using namespace std;

struct fenwick_tree
{
    uint32_t n;
    vector<uint32_t> F;
    fenwick_tree(uint32_t _n) : n(_n), F(n+1) {}
    void delta(uint32_t p, uint32_t v)
    {
        p++;
        while(p <= n)
            F[p] += v, p += (p & -p);
    }
    uint32_t get_prefix(uint32_t p) const
    {
        uint32_t r = 0;
        while(p)
            r += F[p], p -= (p & -p);
        return r;
    }
};

int main()
{
    uint32_t n;
    cin >> n;
    vector<pair<uint32_t, uint32_t>> B(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> B[i].first, B[i].second = i;
    sort(B.begin(), B.end());
    vector<uint32_t> A(n+2);
    uint32_t maxA;
    {
        uint32_t f = 0;
        for(uint32_t i = 0; i < n; i++)
        {
            if(i and B[i].first == B[i-1].first)
                f++;
            A[B[i].second+1] = i - f + 1;
        }
        maxA = n - f + 1;
    }
    A[0] = maxA; A[n+1] = 0;
    vector<pair<uint32_t, uint32_t>> Q;
    for(uint32_t i = 1; i <= n; i++)
        if(A[i] > A[i-1])
            Q.back().second++;
        else
            Q.emplace_back(i, i);
    fenwick_tree M(maxA+4);
    for(uint32_t i = 1; i <= n; i++)
        M.delta(A[i], 1);
    uint32_t result = 0;

    for(uint32_t q = 0; q < Q.size(); q++)
    {
        uint32_t a = Q[q].first, b = Q[q].second;
        for(uint32_t i = a; i <= b; i++)
            M.delta(A[i], -1);

        result = max(result, b - a + 1);
        if(1 < a and M.get_prefix(A[a]))
            REG(b - a + 2);
        if(b < n and M.get_prefix(maxA+1) > M.get_prefix(A[b]+1))
            REG(b - a + 2);
        if(1 < a and b < n and A[b+1] < A[a] and A[b] < A[a-1])
            REG(b - a + 3);
        if(1 < a and a < b and A[a] < A[a-1] and A[a-1] < A[a+1])
            REG(b - a + 2);
        if(b < n and a < b and A[b-1] < A[b+1] and A[b+1] < A[b])
            REG(b - a + 2);

        for(uint32_t i = a; i <= b; i++)
            M.delta(A[i], 1);
    }

    if(Q.size() >= 2)
    {
        for(uint32_t i = Q[0].first; i <= Q[0].second; i++)
            M.delta(A[i], -1);
        for(uint32_t q = 1; q < Q.size(); q++)
        {
            uint32_t a = Q[q-1].first, b = Q[q-1].second, c = Q[q].second;
            for(uint32_t i = b+1; i <= c; i++)
                M.delta(A[i], -1);
            if(a == b and b == c-1 and A[b] > A[c])
                REG(2u);
            if(b+1 < c and a < b and A[b] < A[b+2] and A[b-1] < A[b+1] and A[b+1] < A[b])
                REG(c - a + 1);
            if(a < b and M.get_prefix(A[b+1]) > M.get_prefix(A[b-1]+1))
                REG(c - a + 1);
            if(b+1 < c and M.get_prefix(A[b+2]) > M.get_prefix(A[b]+1))
                REG(c - a + 1);
            if(a < b and c < n and A[b-1] < A[c+1] and A[c+1] < A[b+1] and A[c] < A[b])
                REG(c - a + 2);
            if(b+1 < n and a > 1 and A[b] < A[a-1] and A[a-1] < A[b+2] and A[b+1] < A[a])
                REG(c - a + 2);

            for(uint32_t i = a; i <= b; i++)
                M.delta(A[i], 1);
        }
        for(uint32_t i = Q.back().first; i <= Q.back().second; i++)
            M.delta(A[i], 1);
    }
    if(Q.size() >= 3)
    {
        for(uint32_t i = Q[0].first; i <= Q[1].second; i++)
            M.delta(A[i], -1);
        for(uint32_t q = 2; q < Q.size(); q++)
        {
            uint32_t a = Q[q-2].first, b = Q[q-2].second, c = Q[q-1].second, d = Q[q].second;
            for(uint32_t i = c+1; i <= d; i++)
                M.delta(A[i], -1);

            if(a < b and b < c and c+1 < d and A[c] < A[b] and A[b] < A[c+2] and A[b-1] < A[c+1] and A[c+1] < A[b+1])
                REG(d - a + 1);

            for(uint32_t i = a; i <= b; i++)
                M.delta(A[i], 1);
        }
        for(uint32_t i = Q.end()[-2].first; i <= Q.end()[-1].second; i++)
            M.delta(A[i], 1);
    }

    cout << result;
}
