#include <bits/stdc++.h>

using namespace std;

const int oo = 2e9;
const size_t JUMP = 18;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    vector<int> A(n + 1);
    vector<int64_t> S(n + 1);
    for(size_t i = 0; i < n; i++)
        cin >> A[i];
    A[n] = +oo;

    for(size_t i = 0; i < n; i++)
        S[i+1] = S[i] + A[i];
    auto sum = [&](size_t i, size_t j) {
        return S[j] - S[i];
    };

    vector<array<pair<size_t, int64_t>, JUMP>> jump(n + 1);
    vector<pair<int, size_t>> cat = {{A.back(), n}};
    for(size_t j = 0; j < JUMP; j++)
        jump[n][j] = {n, 0};
    for(size_t i = n; i --> 0; )
    {
        auto c = pair(A[i], i);
        while(c >= cat.back())
            cat.pop_back();
        size_t p = cat.back().second;
        jump[i][0] = {p, int64_t(p-i)*A[i] - sum(i, p)};
        for(size_t j = 0; j+1 < JUMP; j++)
        {
            auto [i1, w1] = jump[i][j];
            auto [i2, w2] = jump[i1][j];
            jump[i][j+1] = {i2, w1 + w2};
        }
        cat.push_back(c);
    }

    while(q --> 0)
    {
        size_t a, b;
        cin >> a >> b; a--;

        size_t i = a;
        int64_t w = 0;
        for(size_t j = JUMP; j --> 0; )
            if(jump[i][j].first <= b)
                w += jump[i][j].second, i = jump[i][j].first;
        w += int64_t(b - i)*A[i] - sum(i, b);

        cout << w << '\n';
    }
}
