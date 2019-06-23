#include <bits/stdc++.h>

using namespace std;

struct dt
{
    size_t i; uint64_t n, d;
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n, k;
    cin >> n >> k;
    vector<dt> A(n);
    for(size_t i = 0; i < n; i++)
        A[i].i = i, cin >> A[i].n >> A[i].d;

    nth_element(A.begin(), A.end() - k, A.end(), [](const dt& lhs, const dt& rhs) {
        return make_pair(lhs.n * rhs.d, lhs.i) < make_pair(rhs.n * lhs.d, rhs.i);
    });

    for(size_t i = n - k; i < n; i++)
        cout << A[i].i+1 << " ";
}
