#include <bits/stdc++.h>

using namespace std;

struct mul_segment_tree
{
    size_t w;
    vector<uint> values;
    uint m;

    mul_segment_tree(size_t n, uint _m)
        : w(1 << __lg(2*n-1)), values(2*w, 1), m(_m) {}

    uint F(uint a, uint b) { return (uint64_t)a * b % m; }

    uint& leaf(size_t p) { return values[w + p]; }
    void rebuild()
    {
        for(size_t i = w; i --> 1; )
            values[i] = F(values[2*i], values[2*i+1]);
    }

    void set(size_t p, uint v)
    {
        p += w;
        values[p] = v;
        while(p /= 2)
            values[p] = F(values[2*p], values[2*p+1]);
    }

    uint get(size_t L, size_t R)
    {
        uint result = 1;
        for(L += w, R += w; L < R; L /= 2, R /= 2)
        {
            if(L % 2) result = F(result, values[L++]);
            if(R % 2) result = F(result, values[--R]);
        }
        return result;
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q; uint m;
    cin >> n >> m >> q;

    mul_segment_tree T(n, m);

    for(size_t i = 0; i < n; i++)
        cin >> T.leaf(i);
    T.rebuild();

    vector<size_t> B(n);

    while(q --> 0)
    {
        size_t c;
        cin >> c;
        if(c == 0)
        {
            size_t p; uint v;
            cin >> p >> v; p--;
            T.set(p, v);
        }
        else if(c == 1)
        {
            size_t k;
            cin >> k;

            for(size_t i = 0; i < k; i++)
                cin >> B[i], B[i]--;
            sort(B.begin(), B.begin() + k);

            uint result = 1;
            size_t a = 0;
            for(size_t i = 0; i < k; a = B[i++] + 1)
                result = (uint64_t) result * T.get(a, B[i]) % m;
            result = (uint64_t) result * T.get(a, n) % m;

            cout << result % m << '\n';
        }
    }
}
