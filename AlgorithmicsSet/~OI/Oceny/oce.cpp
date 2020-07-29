#include <bits/stdc++.h>

using namespace std;


struct cover_tree
{
    size_t w;
    vector<pair<int, size_t>> values;
    vector<int> delta;

    cover_tree(size_t n) : w(1 << __lg(2*n-1)), values(2*w), delta(2*w)
    {
        for(size_t i = w; i < 2*w; i++)
            values[i] = {0, 1};
        for(size_t i = w; i --> 1; )
            values[i] = {0, values[2*i].second + values[2*i+1].second};
    }

    pair<int, size_t> f(pair<int, size_t> a, pair<int, size_t> b)
    {
        if(a.first == b.first)
            return {a.first, a.second + b.second};
        else
            return a.first < b.first ? a : b;
    }

    void update(size_t i)
    {
        if(i < w)
            delta[2*i] += delta[i], delta[2*i+1] += delta[i];
        values[i].first += delta[i];
        delta[i] = 0;
    }

    void add(size_t i, size_t nodeL, size_t nodeR, size_t getL, size_t getR, int v)
    {
        update(i);
        if(nodeR < getL or getR < nodeL)
            return;
        else if(getL <= nodeL and nodeR <= getR)
            delta[i] += v, update(i);
        else
        {
            add(2*i, nodeL, (nodeL+nodeR)/2, getL, getR, v);
            add(2*i+1, (nodeL+nodeR)/2+1, nodeR, getL, getR, v);
            values[i] = f(values[2*i], values[2*i+1]);
        }
    }

    size_t cover() const { return w - (values[1].first == 0 ? values[1].second : 0); }
};


int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    vector<size_t> A(n+2);
    for(size_t i = 1; i <= n; i++)
        cin >> A[i];
    A[n+1] = n+1;

    vector<size_t> P(n+2);
    for(size_t i = 0; i <= n+1; i++)
        P[A[i]] = i;

    cover_tree cov(n+1);
    auto toggle = [&](size_t a, int v) {
        if(P[a] > P[a+1])
            cov.add(1, 0, cov.w-1, P[a+1], P[a]-1, v);
    };

    for(size_t i = 0; i <= n; i++)
        toggle(i, +1);

    auto answer = [&]() {
        return n - cov.cover();
    };

    cout << answer() << '\n';

    while(q --> 1)
    {
        size_t i, j;
        cin >> i >> j;

        size_t &a = A[i], &b = A[j];

        toggle(a-1, -1);
        toggle(a, -1);
        if(b-1 != a-1 and b-1 != a)
            toggle(b-1, -1);
        if(b != a-1 and b != a)
            toggle(b, -1);

        swap(a, b);
        swap(P[a], P[b]);

        toggle(a-1, +1);
        toggle(a, +1);
        if(b-1 != a-1 and b-1 != a)
            toggle(b-1, +1);
        if(b != a-1 and b != a)
            toggle(b, +1);

        cout << answer() << '\n';
    }
}
