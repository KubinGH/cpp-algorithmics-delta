#include <bits/stdc++.h>

using namespace std;

struct dt { int64_t cnt[2], ret; };
const int oo = 1e9;

const dt neutral = {{0, 0}, 0};

dt operator| (const dt& lhs, const dt& rhs)
{
    return {
        {lhs.cnt[0] + rhs.cnt[0], lhs.cnt[1] + rhs.cnt[1]},
        lhs.ret + rhs.ret + lhs.cnt[0] * rhs.cnt[1]
    };
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
            T[w+i] = neutral;
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

    dt get(size_t i, size_t nodeL, size_t nodeR, size_t getL, size_t getR)
    {
        if(nodeR < getL or nodeL > getR)
            return neutral;
        else if(getL <= nodeL and nodeR <= getR)
            return T[i];
        else
            return get(2*i, nodeL, (nodeL+nodeR)/2, getL, getR)
                 | get(2*i+1, (nodeL+nodeR)/2+1, nodeR, getL, getR);
    }
    dt get(size_t getL, size_t getR) { return get(1, 0, w-1, getL, getR); }

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
        A[i] = (S[i] == 'K');

    segment_tree T(n);
    auto refresh = [&](size_t i) {
        if(A[i])
            T.set(i, {{0, 1}, 0});
        else
            T.set(i, {{1, 0}, 0});
    };
    for(size_t i = 0; i < n; i++)
        refresh(i);

    while(m --> 0)
    {
        char c;
        cin >> c;
        if(c == 'X')
        {
            size_t p;
            cin >> p; p--;
            A[p] = not A[p];
            refresh(p);
        }
        else if(c == '?')
        {
            size_t l, r;
            cin >> l >> r; l--; r--;
            cout << T.get(l, r).ret << '\n';
        }
    }
}
