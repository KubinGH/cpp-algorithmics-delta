#include <bits/stdc++.h>

using namespace std;

template<typename U, typename V>
vector<pair<U, V>> attached(vector<U> a, V v)
{
    vector<pair<U, V>> b;
    for(const auto& x : a) b.emplace_back(x, v);
    return b;
}

pair<size_t, size_t> solve(vector<size_t> A, vector<size_t> B, size_t n)
{
    auto Ea = attached(A, false), Eb = attached(B, true);
    vector<pair<size_t, bool>> E;
    merge(Ea.begin(), Ea.end(), Eb.begin(), Eb.end(), back_inserter(E));

    size_t minim = 0, maxim = 0;

    using dt = array<array<size_t, 2>, 2>;

    dt called = { {{n, 0}, {0, 0}} };

    auto call = [&](array<size_t, 2> i, size_t t) {
        called[i[0]][i[1]]--;
        i[t]++;
        called[i[0]][i[1]]++;
    };

    auto smart_call = [&](size_t t) {
        array<size_t, 2> i = {0, 0}; i[t^1]++;
        if(called[0][0]) { call({0, 0}, t); return 1; }
        else             { call(     i, t); return 0; }
    };

    auto dumb_call = [&](size_t t) {
        array<size_t, 2> i = {0, 0}; i[t^1]++;
        if(called[i[0]][i[1]]) { call(     i, t); return 0; }
        else                   { call({0, 0}, t); return 1; }
    };

    for(auto [t, p] : E)
        if(p)
            smart_call(1);
        else
            minim += dumb_call(0);

    called[0][0] = n;
    called[1][0] = called[0][1] = called[1][1] = 0;

    for(auto [t, p] : E)
        if(p)
            dumb_call(1);
        else
            maxim += smart_call(0);
    return {minim, maxim};
}

int main()
{
#ifndef XHOVA
    ifstream cin("friends.in");
    ofstream cout("friends.out");
#endif

    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, a, b;
    cin >> n >> a >> b;

    vector<size_t> A(a), B(b);
    for(auto& x : A) cin >> x;
    for(auto& x : B) cin >> x;

    auto [u1, u2] = solve(A, B, n);
    auto [v1, v2] = solve(B, A, n);
    cout << u1 << ' ' << u2 << '\n' << v1 << ' ' << v2 << '\n';
}
