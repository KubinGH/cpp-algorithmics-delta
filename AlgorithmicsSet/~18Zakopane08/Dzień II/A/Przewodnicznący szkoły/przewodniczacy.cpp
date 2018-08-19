#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 7e4 + 32;

typedef tuple<uint32_t, uint32_t, uint32_t> query_t;

uint32_t solve(uint32_t a, uint32_t b, int32_t (&A)[MAX], int32_t (&B)[MAX], int32_t (&S)[MAX])
{
    uint32_t m = b - a + 1;
    for(uint32_t i = 0; i < m; i++)
        B[i] = A[a+i];
    for(uint32_t i = 0; i < m; i++)
        B[m+i] = -A[a+i];
    uint32_t r = 0;
    for(uint32_t i = 0; i < m; i++)
    {
        S[i+1] = S[i] + B[i];
        if(S[i+1] < 0)
        {
            S[i+1] += 1;
            B[m+i] -= 1;
            r++;
        }
    }
    int32_t minim = 0;
    for(uint32_t i = m; i < 2*m; i++)
    {
        S[i+1] = S[i] + B[i];
        minim = min(minim, S[i+1]);
    }
    return r + (-minim);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    uint32_t Q = floor(sqrt(n) - 1);
    auto mo_cmp = [&](const query_t& lhs, const query_t& rhs) {
        if(get<0>(lhs) / Q != get<0>(rhs) / Q)
            return get<0>(lhs) / Q < get<0>(rhs) / Q;
        else
            return get<1>(lhs) > get<1>(rhs);
    };
    static char I[MAX];
    cin >> I;
    static int32_t A[MAX];
    for(uint32_t i = 0; i < n; i++)
        A[i] = (I[i] == 'C') ? 1 : -1;
    static int32_t U[MAX];
    for(uint32_t i = 0; i < n; i++)
        U[i+1] = U[i] + A[i];
    auto sum = [&](uint32_t l, uint32_t r){ return U[r+1] - U[l]; };
    static query_t queries[MAX];
    uint32_t q;
    cin >> q;
    for(uint32_t i = 0; i < q; i++)
    {
        uint32_t a, b;
        cin >> a >> b; a--; b--;
        queries[i] = query_t{a, b, i};
    }
    if(n > 4) sort(queries, queries + q, mo_cmp);
    static uint32_t results[MAX];
    static int32_t B[MAX], S[MAX];
    for(uint32_t i = 0; i < q; i++)
    {
        uint32_t a, b, qi;
        tie(a, b, qi) = queries[i];
        results[qi] = solve(a, b, A, B, S);
    }
    for(uint32_t i = 0; i < q; i++)
        cout << results[i] << "\n";
}
