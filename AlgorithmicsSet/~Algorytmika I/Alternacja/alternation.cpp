#include <bits/stdc++.h>

using namespace std;

using dt = array<array<int, 2>, 2>;
const int oo = 1e9;

dt operator| (const dt& lhs, const dt& rhs)
{
    dt out = {{{-oo, -oo}, {-oo, -oo}}};
    for(uint a = 0; a < 2; a++)
      for(uint b = 0; b < 2; b++)
        out[a][b] = max(lhs[a][b], rhs[a][b]);
    for(uint a = 0; a < 2; a++)
      for(uint b = 0; b < 2; b++)
        for(uint c = 0; c < 2; c++)
          out[a][c] = max(out[a][c], lhs[a][b] + rhs[!b][c]);
    return out;
}

struct segment_tree
{
    size_t w;
    vector<dt> T;
    segment_tree(size_t n)
    {
        w = 1 << __lg(2*n-1);
        T.resize(2*w);
        for(size_t i = 0; i < w; i++)
            T[w+i] = {{{-oo, -oo}, {-oo, -oo}}};
        for(size_t i = w; i --> 1; )
            T[i] = T[2*i] | T[2*i+1];
    }
    void set(size_t p, dt v)
    {
        p += w;
        T[p] = v;
        while(p > 1)
            p /= 2, T[p] = T[2*p] | T[2*p+1];
    }
    dt get() { return T[1]; }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<bool> A(n);
    string S;
    cin >> S;
    for(size_t i = 0; i < n; i++)
        A[i] = (S[i] == '1');

    segment_tree T(n);
    auto refresh = [&](size_t i) {
        if(A[i])
            T.set(i, {{{-oo, -oo}, {-oo, 1}}});
        else
            T.set(i, {{{1, -oo}, {-oo, -oo}}});
    };
    auto get = [&]() {
        dt x = T.get();
        return max({x[0][0], x[0][1], x[1][0], x[1][1]});
    };
    for(size_t i = 0; i < n; i++)
        refresh(i);

    cout << get() << ' ';
    while(m --> 0)
    {
        size_t i;
        cin >> i; i--;

        A[i] = not A[i];
        refresh(i);

        cout << get() << ' ';
    }
}
