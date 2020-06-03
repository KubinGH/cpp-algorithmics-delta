#include <bits/stdc++.h>

using namespace std;

struct query_t
{
    size_t i, L, R; uint64_t d;
};

// https://en.wikipedia.org/wiki/Hilbert_curve
uint64_t hilbert_line(size_t n, size_t x, size_t y)
{
    uint64_t d = 0;
    for(size_t s = n/2; s; s /= 2)
    {
        bool rotx = x & s, roty = y & s;
        d += (uint64_t) s * s * ((3 * (uint)rotx) ^ (uint)roty);
        if(not roty)
        {
            if(rotx)
                x = n-1 - x, y = n-1 - y;
            swap(x, y);
        }
    }
    return d;
}


int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    size_t m = 1 << __lg(2*n-1);

    vector<int> A(n);
    for(auto& a : A)
        cin >> a;

    vector<query_t> Q(q);
    for(size_t i = 0; i < q; i++)
    {
        Q[i].i = i;
        cin >> Q[i].L >> Q[i].R; Q[i].L--;
        Q[i].d = hilbert_line(m, Q[i].L, Q[i].R);
    }

    vector<size_t> I(q);
    iota(I.begin(), I.end(), 0);
    sort(I.begin(), I.end(), [&](size_t lhs, size_t rhs) {
        return Q[lhs].d < Q[rhs].d;
    });

    size_t L = 0, R = 0;
    int64_t result = 0;
    vector<int> C(*max_element(A.begin(), A.end()) + 1);
    auto push = [&](int x) {
        result += (int64_t) x * (2*(++C[x])-1);
    };
    auto pop = [&](int x) {
        result -= (int64_t) x * (2*(C[x]--)-1);
    };

    vector<int64_t> answers(q);
    for(size_t i : I)
    {
        while(R < Q[i].R) push(A[R++]);
        while(L > Q[i].L) push(A[--L]);
        while(R > Q[i].R) pop(A[--R]);
        while(L < Q[i].L) pop(A[L++]);
        answers[i] = result;
    }

    for(auto a : answers)
        cout << a << '\n';
}
